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

#define PI 3.14159265358979323846

// storing cuda device properties, for the sheduling of parallel computing
static cudaDeviceProp prop;

// data
VortexMarker_t* wake_markers; // on-host array containing all of the markers, for convenience mem copying with GPU
VortexMarker_t* dev_wake_markers; // on-device array ...
int* idx_end_marker_fila; // on-host array containing index of endpoint of all vortex filaments, for parallel computing
int* dev_idx_end_marker_fila; // on-device array ...

// vel += biot savert induction from segement a-b to position p
__device__ float3 biot_savart_induction(VortexMarker_t a, VortexMarker_t b, float3 p, float3 vel)
{
    float3 ap, bp, ab, ba, ind;
    float dbnrm_ab, dbnrm_ap, dbnrm_bp; // |vector|^2
    float rnrm_ind; // 1/norm(vector) 
    float cos_apab, cos_babp, db_sin_apab;
    float h, scale;

    // if marker a or b is at p, pass
    if ( a.pos[0]==p.x && a.pos[1]==p.y && a.pos[2]==p.z ||
         b.pos[0]==p.x && b.pos[1]==p.y && b.pos[2]==p.z ||
         a.pos[0]==b.pos[0] && a.pos[1]==b.pos[1] && a.pos[2]==b.pos[2]) {
        return vel;
    }

    // get vectors AP, BP and AB & BA  [12 FLOPS]
    //  AP [3 FLOPS]
    /*
    ap.x = p.x - a.pos[0];
    ap.y = p.y - a.pos[1];
    ap.z = p.z - a.pos[2];
    */
    ap.x = __fsub_ru(p.x, a.pos[0]);
    ap.y = __fsub_ru(p.y, a.pos[1]);
    ap.z = __fsub_ru(p.z, a.pos[2]);
    //  BP [3 FLOPS]
    /*
    bp.x = p.x - b.pos[0];
    bp.y = p.y - b.pos[1];
    bp.z = p.z - b.pos[2];
    */
    bp.x = __fsub_ru(p.x, b.pos[0]);
    bp.y = __fsub_ru(p.y, b.pos[1]);
    bp.z = __fsub_ru(p.z, b.pos[2]);
    //  AB [3 FLOPS]
    /*
    ab.x = b.pos[0] - a.pos[0];
    ab.y = b.pos[1] - a.pos[1];
    ab.z = b.pos[2] - a.pos[2];
    */
    ab.x = __fsub_ru(b.pos[0], a.pos[0]);
    ab.y = __fsub_ru(b.pos[1], a.pos[1]);
    ab.z = __fsub_ru(b.pos[2], a.pos[2]);
    //  BA [3 FLOPS]
    /*
    ba.x = a.pos[0] - b.pos[0];
    ba.y = a.pos[1] - b.pos[1];
    ba.z = a.pos[2] - b.pos[2];
    */
    ba.x = __fsub_ru(a.pos[0], b.pos[0]);
    ba.y = __fsub_ru(a.pos[1], b.pos[1]);
    ba.z = __fsub_ru(a.pos[2], b.pos[2]);

    // cos(ap-ab) and cos(ba-bp) [31 FLOPS]
    dbnrm_ab = ab.x*ab.x + ab.y*ab.y + ab.z*ab.z; // [5 FLOPS]
    dbnrm_ap = ap.x*ap.x + ap.y*ap.y + ap.z*ap.z; // [5 FLOPS]
    dbnrm_bp = bp.x*bp.x + bp.y*bp.y + bp.z*bp.z; // [5 FLOPS] 
    cos_apab = (ap.x*ab.x + ap.y*ab.y + ap.z*ab.z)*__frsqrt_rn(dbnrm_ap*dbnrm_ab); // [8 FLOPS]
    cos_babp = (ba.x*bp.x + ba.y*bp.y + ba.z*bp.z)*__frsqrt_rn(dbnrm_ab*dbnrm_bp); // [8 FLOPS]

    // h, perpendicular distance from P to AB [5 FLOPS]
    db_sin_apab = 1-cos_apab*cos_apab; //[2 FLOPS]
    if (db_sin_apab <= 0.0f) // sometimes |cos_apab| will be slightly larger than 1.0f due to computation err
        h = 0.0f;
    else
        h = __fsqrt_ru(dbnrm_ap) * __fsqrt_ru(db_sin_apab); // [3 FLOPS]
if (h != h)
    printf("fuck");

    // strength
    scale = a.Gamma * (h/(0.0001+h*h)) * (cos_apab+cos_babp) / (4*PI);
 
if (scale != scale)
    printf("vel.x = %f, scale = %f, h = %f\n", vel.x, scale, h);

    // get induced velocity
    ind.x = ap.y*bp.z - ap.z*bp.y;
    ind.y = ap.z*bp.x - ap.x*bp.z;
    ind.z = ap.x*bp.y - ap.y*bp.x;
    rnrm_ind = __frsqrt_rn(ind.x*ind.x + ind.y*ind.y + ind.z*ind.z);
    scale = scale * rnrm_ind;
    ind.x = scale * ind.x;
    ind.y = scale * ind.y;
    ind.z = scale * ind.z;

    // add induced velocity [3 FLOPS]
    vel.x += ind.x;
    vel.y += ind.y;
    vel.z += ind.z;

if (vel.x != vel.x)
    printf("vel.x = %f, scale = %f, h = %f\n", vel.x, scale, h);

    return vel;
}

__device__ float3 tile_calculation_vel_markers
(float3 pos, float3 vel, int tile, int tile_size,int row_sgmts, VortexMarker_t* markers, int* index_end, int num_fila, int num_markers)
{
    int i; // the i-th colum marker in this tile
    int idx_m; // the idx_m -th colum marker of whole N markers
    int idx_fila; // index of fila
    int shared_mem_offset = (tile%row_sgmts)*tile_size;

    bool isend; // the marker to be calculated is an end point or not

    extern __shared__ VortexMarker_t tile_markers[];
 
    // if this tile is not the first tile, we will use the last tile's end
    if (tile > 0)
    {
        isend = false;
        for (idx_fila = 0; idx_fila < num_fila; idx_fila++) {
            if (tile*tile_size-1 == index_end[idx_fila]) {
                isend = true;
                break;
            }
        }
        if (isend == false && tile*tile_size < num_markers)
            vel = biot_savart_induction(markers[tile*tile_size-1], tile_markers[shared_mem_offset], pos, vel); 
    }

    for (i = 0; i < tile_size-1; i++)
    {// compule all colum markers in this tile
        idx_m = tile * tile_size + i;
        if (idx_m >= num_markers-1)
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
                vel = biot_savart_induction(tile_markers[shared_mem_offset+i], tile_markers[shared_mem_offset+i+1], pos, vel);
        }
    }

    return vel;
}

/* calculate velocities of markers, running on GPU
Note:
    This routine uses one-dimensional blocks and threads
    row_sgms is the number of segments to parallelly compute a row
    blockDim must equal to tile_size*row_sgmts
    gridDim == (num_markers + tile_size - 1) / tile_size
 */
__global__ void CalculateVelofMarkers(VortexMarker_t* markers, int* idx_end, int num_fila, int num_markers, int tile_size, int row_sgmts)
{
    extern __shared__ VortexMarker_t tile_markers[];

    int idx, i;
    float3 pos; // position of vortex marker to calculate velocity in this thread
    float3 vel = {0.0f, 0.0f, 0.0f}; // velocity of this marker
    int row = threadIdx.x%tile_size + blockIdx.x*tile_size; // get row number (the index of marker to be evaluated)

    // get the marker of which the velocity to be calculated
    if (row < num_markers) {
        pos.x = markers[row].pos[0];
        pos.y = markers[row].pos[1];
        pos.z = markers[row].pos[2];
    }

    // compute each tile
    i = 0;
    while(true) // every thread can enter this loop
    {
        idx = threadIdx.x + blockDim.x*i;
        if (idx < num_markers)
            tile_markers[threadIdx.x] = markers[idx]; // copy markers to shared mem for tile calculation 
        __syncthreads(); // make sure the shared mem has been loaded
        if (row < num_markers)
            vel = tile_calculation_vel_markers(pos, vel, idx/tile_size, tile_size, row_sgmts, markers, idx_end, num_fila, num_markers);
        __syncthreads(); // make sure every thread has done the calc of this tile
        
        if (blockDim.x*(i+1) < num_markers)
            i++;
        else
            break;
    }

    // save the result of this segment to the end of the shared mem
    //  at present the shared memory is of no use for computation, so it can be used to temporarily store the segment results
    if (row < num_markers) {
        tile_markers[threadIdx.x].vel[0] = vel.x;
        tile_markers[threadIdx.x].vel[1] = vel.y;
        tile_markers[threadIdx.x].vel[2] = vel.z;
    }
    __syncthreads(); // make sure the segment results are stored
 
    if (threadIdx.x < tile_size && row < num_markers) {
        // sum the velocities computed by multiple (num of row_sgms) threads
        vel.x = 0.0f; vel.y = 0.0f; vel.z = 0.0f;
        for (i = 0; i < row_sgmts; i++) {
            vel.x += tile_markers[threadIdx.x%tile_size+i*tile_size].vel[0];
            vel.y += tile_markers[threadIdx.x%tile_size+i*tile_size].vel[1];
            vel.z += tile_markers[threadIdx.x%tile_size+i*tile_size].vel[2];
        }
        // Save the result in global memory for the integration step.
        markers[row].vel[0] = vel.x;
        markers[row].vel[1] = vel.y;
        markers[row].vel[2] = vel.z;

        markers[row].pos[0] += vel.x*0.01;
        markers[row].pos[1] += vel.y*0.01;
        markers[row].pos[2] += vel.z*0.01;
    }
}
#if 0
/* calculate new positions of markers, running on GPU */
__global__ void CalculatePosofMarkers(VortexMarker_t* markers, int num_markers)
{
    VortexMarker_t mkr;
    float3 pos, vel;
    int tid = threadIdx.x + blockIdx.x * blockDim.x;

    if (tid < num_markers) {
        mkr = markers[tid];

        for (int i = 0; i < 3; i++)
            mkr.pos[i] = mkr.vel[i]*0.01;
    }
    __syncthreads();
    if (tid < num_markers)
        markers[tid] = mkr;
}
#endif

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
    int p, q, threads, blocks;
    p = prop.warpSize; // tile size
    q = 2; // number of segments of a row
    threads = std::min(p*q, prop.maxThreadsPerBlock);
    blocks = (addr_cp_markers + p - 1) / p;
    //  Note: here omitted checks for max number of blocks, since in RAO problem the vortex markers
    //        rarely exceeds 65535*threads.

    //  launch gpu computing
    //   the end address of shared memory contains the end element of 'last' tile for 'next' tile computation
    cudaError_t err;
    CalculateVelofMarkers<<<blocks, threads, (threads)*sizeof(VortexMarker_t)>>>(dev_wake_markers, dev_idx_end_marker_fila, num_blade, addr_cp_markers, p, q);
    err = cudaGetLastError();
    if (err != cudaSuccess) 
        printf("Error: %s\n", cudaGetErrorString(err));
#if 0
    CalculatePosofMarkers<<<blocks, threads>>>(dev_wake_markers, addr_cp_markers);
    err = cudaGetLastError();
    if (err != cudaSuccess) 
        printf("Error: %s\n", cudaGetErrorString(err));
#endif
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
            robots->at(idx_robot)->wakes.at(idx_rotor)->maintain();
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
