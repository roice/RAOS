/*
 * Wakes in the simulation environment
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-03-08 create this file (RAOS)
 */

#include <stdio.h>
#include "model/robot.h"
#include "model/wake_rotor.h"
#include "model/error_cuda.h"

// storing cuda device properties, for the sheduling of parallel computing
static cudaDeviceProp prop;

// data
VortexMarker_t* wake_markers; // on-host array containing all of the markers, for convenience mem copying with GPU
VortexMarker_t* dev_wake_markers; // on-device array ...
int* idx_end_marker_fila; // on-host array containing index of endpoint of all vortex filaments, for parallel computing
int* dev_idx_end_marker_fila; // on-device array ...

__device__ float3 tile_calculation_vel_markers
(VortexMarker_t vtx_mkr, float3 vel, int tile, int* index_end, int num_fila)
{
    int i; // the i-th colum marker in this tile
    int idx_m; // the idx_m -th colum marker of whole N markers
    int idx_fila; // index of fila

    bool isend; // the marker to be calculated is an end point or not

    static VortexMarker_t prev_tile_end; // the last marker of previous tile
    static int idx_pre_tile_end; // the index of ...

    extern __shared__ VortexMarker_t tile_markers[threadsPerBlock];
   
    // if this tile is not the first tile, we will use the last tile's end
    if (tile != 0)
    {
        isend = false;
        for (idx_fila = 0; idx_fila < num_fila; idx_fila++) {
            if (idx_pre_tile_end == index_end[idx_fila]) {
                isend = true;
                break;
            }
        }
        if (isend == false)
            biot_savart_induction(prev_tile_end, tile_markers[0], ...);
    }

    for (i = 0; i < blockDim.x -1; i++)
    {// compule all colum markers in this tile
        idx_m = tile * blockDim.x + i;
        if (idx_m >= num_markers)
            break;
        else
        {
            isend = false;
            // check whether this marker is end point or not
            for (idx_fila = 0; idx_fila < num_fila; idx_fila++) {
                if (idx_m == index_end[idx_fila]) {
                    isend = true;
                    break;
                }
            }
            if (isend == false) // if this marker is not an end point
                biot_savart_induction();

            if (i == blockDim.x-2)
            {// save the last marker of this tile for the computation of next tile
                prev_tile_end = tile_markers[blockDim.x-1];
                idx_pre_tile_end = idx_m+1;
            }
        }
    }
}

/* calculate velocities of markers, running on GPU
 */
__global__ void CalculateVelofMarkers(VortexMarker_t* markers, int* idx_end, int num_fila)
{
    extern __shared__ VortexMarker_t tile_markers[threadsPerBlock];

    int i = 0, tile = 0, idx;
    VortexMarker_t vtx_mkr; // vortex marker to calculate velocity in this thread
    float3 vel = {0.0f, 0.0f, 0.0f};
    int tid = threadIdx.x + blockIdx.x * blockDim.x; // get ID of this thread

    // get the marker of which the velocity to be calculated
    if (tid < num_markers)
        vtx_mkr = markers[tid]; // in C++, struct can be directly assigned

    while (1) // every thread can enter this loop
    {
        idx = tile * blockDim.x + threadIdx.x;
        if (idx < num_markers)
            tile_markers[threadIdx.x] = markers[idx]; // copy markers to shared mem for tile calculation
        __syncthreads(); // make sure the shared mem has been loaded
        if (idx < num_markers)
            tile_calculation_vel_markers(vtx_mkr, vel, tile, idx_end, num_fila);

    }



    // calculate the velocity of this marker
    for (i = 0, tile = 0; i < num_markers; i += blockDim.x, tile++) 
    {
         
__syncthreads();
acc = tile_calculation(myPosition, acc);
__syncthreads();
}
// Save the result in global memory for the integration step.
float4 acc4 = {acc.x, acc.y, acc.z, 0.0f};
globalA[gtid] = acc4;

}


/* update all of the rotor wakes in the environment
 * this routine will traverse all of the robot instances
 * and update all of the Lagrangian markers for all robots */
void WakesUpdate(std::vector<Robot*>* robots)
{
    int idx_robot, idx_rotor, idx_blade;
    int num_blade = 0;
    int addr_cp_markers = 0; // index for copy marker states from rotor wake to wake_markers

/* Step 1: update velocity & position of markers */
 
    // Phase 1: collect all vortex markers to a memory, for GPU computing
    //  the markers are placed contiguously, fila to fila
    for(idx_robot = 0; idx_robot < robots->size(); idx_robot++) {
        for (idx_rotor = 0; idx_rotor < robots->at(idx_robot)->wakes.size(); idx_rotor++) {
            for (idx_blade = 0; idx_blade < robots->at(idx_robot)->wakes.at(idx_rotor)->rotor_state.frame.n_blades; idx_blade++) {
                std::copy(robots->at(idx_robot)->wakes.at(idx_rotor)->wake_state[idx_blade]->begin(),
                    robots->at(idx_robot)->wakes.at(idx_rotor)->wake_state[idx_blade]->end(),
                    &wake_markers[addr_cp_markers]);
                addr_cp_markers += robots->at(idx_robot)->wakes.at(idx_rotor)->wake_state[idx_blade]->size();
                idx_end_marker_fila[num_blade] = addr_cp_markers-1; // the address of the last element, hence -1
                num_blade++;
            }
        }
    }// traversed all rotor wakes and got total number of markers

    // Phase 2: copy array wake_markers & idx_wake_markers to GPU's dev_wake_markers
    HANDLE_ERROR( cudaMemcpy(dev_wake_markers, wake_markers, 
                addr_cp_markers*sizeof(VortexMarker_t), cudaMemcpyHostToDevice) );
    HANDLE_ERROR( cudaMemcpy(dev_idx_end_marker_fila, idx_end_marker_fila, 
                num_blade*sizeof(int), cudaMemcpyHostToDevice) );
    
    // Phase 3: parallel computing
    //  determine threads per block and blocks number, at present addr_cp_markers contains total num of markers
    int threads, blocks;
    if (addr_cp_markers < 2*prop.warpSize * prop.multiProcessorCount) // N too small, need to cover as many processors as possible
        threads = imin(prop.warpSize, prop.maxThreadsPerBlock);
    else
        threads = imin(2*prop.warpSize, prop.maxThreadsPerBlock);
    blocks = (addr_cp_markers + threads - 1) / threads; // make sure there are enough blocks&threads
    //  Note: here omitted checks for max number of blocks, since in RAO problem the vortex markers
    //        rarely exceeds 65535*threads.

    //  launch gpu computing
    CalculateVelofMarkers<<<blocks, threads>>>(dev_wake_markers, dev_idx_end_marker_fila, num_blade);


    // Phase 4: retrieve data dev_wake_markers from GPU to wake_markers
    HANDLE_ERROR( cudaMemcpy(wake_markers, dev_wake_markers,
                addr_cp_markers*sizeof(VortexMarker_t), cudaMemcpyDeviceToHost) );

    // Phase 5: GPU computed, distribute the memory to every rotor wake states
    addr_cp_markers = 0;
    for(idx_robot = 0; idx_robot < robots->size(); idx_robot++) {
        for (idx_rotor = 0; idx_rotor < robots->at(idx_robot)->wakes.size(); idx_rotor++) {
            for (idx_blade = 0; idx_blade < robots->at(idx_robot)->wakes.at(idx_rotor)->rotor_state.frame.n_blades; idx_blade++) {
                std::copy(&wake_markers[addr_cp_markers],
                    &wake_markers[addr_cp_markers+robots->at(idx_robot)->wakes.at(idx_rotor)->wake_state[idx_blade]->size()],
                robots->at(idx_robot)->wakes.at(idx_rotor)->wake_state[idx_blade]->data());
                addr_cp_markers += robots->at(idx_robot)->wakes.at(idx_rotor)->wake_state[idx_blade]->size();
            }
        }
    }


/* Step 2: maintain markers of wakes */
    for(idx_robot = 0; idx_robot < robots->size(); idx_robot++)
    {
        for (idx_rotor = 0; idx_rotor < robots->at(idx_robot)->wakes.size(); idx_rotor++) {
            robots->at(idx_robot)->wakes[idx_rotor]->maintain();
        }
    }
}

/* init parallelization of wakes computation */
void WakesInit(std::vector<Robot*>* robots)
{
    /* print the properties of all the graphic cards this machine has */ 
    int count; // number of devices
    HANDLE_ERROR( cudaGetDeviceCount(&count) );
    for (int i = 0; i < count; i++) {// print out info of all graphic cards
        HANDLE_ERROR( cudaGetDeviceProperties(&prop, i) );
        printf("======== Card %d ========\n", i+1);
        printf("Graphic card name: %s\n", prop.name);
        printf("Compute Capability: %d.%d\n", prop.major, prop.minor);
        printf("Total global memory: %ld MByte\n", prop.totalGlobalMem/1024/1024);
        printf("Total constant memoty: %ld kByte\n", prop.totalConstMem/1024);
        printf("Multiprocessor count: %d\n", prop.multiProcessorCount);
        printf("Shared mem per mp: %ld\n", prop.sharedMemPerBlock);
        printf("Registers per mp: %d\n", prop.regsPerBlock);
        printf("Threads in warp: %d\n", prop.warpSize);
        printf("Max threads per block: %d\n", prop.maxThreadsPerBlock);
        printf("Max thread dimensions: (%d, %d, %d)\n", prop.maxThreadsDim[0], prop.maxThreadsDim[1], prop.maxThreadsDim[2]);
        printf("Max grid dimensions: (%d, %d, %d)\n", prop.maxGridSize[0], prop.maxGridSize[1], prop.maxGridSize[2]);
        printf("\n");
    }
    if (count > 1) {// multiple graphic cards
        printf("Warning: Multiple graphic cards have been found on this machine. Please modify the function WakeInit in the file src/model/wake.cu to choose the most appropriate card.\n");
        exit(EXIT_FAILURE); // force the user to choose which card to use
    }
    else if (count <= 0) {// no graphic card found
        printf("Error: No graphic cards have been found on this machine. Please run this program on the machine with NVIDIA graphic cards.\n");
        exit(EXIT_FAILURE);
    }

    /* Init GPU computation */
    // Note: the number of rotor wakes & vortex filaments are fixed since simulation starts

    // traverse all rotor wakes and got total max number of markers and fila, for allocating mem
    int max_num_markers = 0;
    int max_num_fila = 0;
    for(int idx_robot = 0; idx_robot < robots->size(); idx_robot++) {// traverse all robots
        for (int idx_rotor = 0; idx_rotor < robots->at(idx_robot)->wakes.size(); idx_rotor++) {// traverse all rotors
            for (int idx_blade = 0; idx_blade < robots->at(idx_robot)->wakes.at(idx_rotor)->rotor_state.frame.n_blades; idx_blade++)
            {// traverse all blades
                max_num_fila++;
                max_num_markers += robots->at(idx_robot)->wakes.at(idx_rotor)->max_markers;
            }
        }
    }

    // allocate a page-locked host memory containing all of the marker states
    HANDLE_ERROR( cudaHostAlloc((void**)&wake_markers, 
        max_num_markers*sizeof(*wake_markers), cudaHostAllocDefault) );
    // allocate device memory as big as the host's
    HANDLE_ERROR( cudaMalloc((void**)&dev_wake_markers, 
        max_num_markers*sizeof(*dev_wake_markers)) );

    // allocate host memory containing the index of wake_markers
    HANDLE_ERROR( cudaHostAlloc((void**)&idx_end_marker_fila,
        max_num_fila*sizeof(*idx_end_marker_fila), cudaHostAllocDefault) );
    // allocate device memory containing the indexes
    HANDLE_ERROR( cudaMalloc((void**)&dev_idx_end_marker_fila,
        max_num_fila*sizeof(*dev_idx_end_marker_fila)) ); 
}

/* close GPU computation */
void WakesFinish(void)
{
    // free device memory
    HANDLE_ERROR( cudaFree(dev_idx_end_marker_fila) );
    HANDLE_ERROR( cudaFree(dev_wake_markers) );
    // free host memory
    HANDLE_ERROR( cudaFreeHost(idx_end_marker_fila) );
    HANDLE_ERROR( cudaFreeHost(wake_markers) );
}

/* End of file wake.cu */
