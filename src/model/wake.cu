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

VortexMarker_t* wake_markers; // on-host array containing all of the markers, for convenience mem copying with GPU
VortexMarker_t* dev_wake_markers; // on-device array ...

/* update all of the rotor wakes in the environment
 * this routine will traverse all of the robot instances
 * and update all of the Lagrangian markers for all robots */
void WakesUpdate(std::vector<Robot*>* robots)
{
    int idx_robot, idx_rotor;
    int idx_wake_markers = 0; // index for copy marker states from rotor wake to wake_markers

/* Step 1: update velocity & position of markers */
 
    // Phase 1: collect all rotor wake states to a memory, for GPU computing
    for(idx_robot = 0; idx_robot < robots->size(); idx_robot++) {
        for (idx_rotor = 0; idx_rotor < robots->at(idx_robot)->wakes.size(); idx_rotor++) {
            std::copy(robots->at(idx_robot)->wakes[idx_rotor]->wake_state.begin(),
                    robots->at(idx_robot)->wakes[idx_rotor]->wake_state.end(),
                    &wake_markers[idx_wake_markers]);
            idx_wake_markers += robots->at(idx_robot)->wakes[idx_rotor]->wake_state.size();
        }
    }// traversed all rotor wakes and got total number of markers

    // Phase 2: copy array wake_markers to GPU's dev_wake_markers
    HANDLE_ERROR( cudaMemcpy(dev_wake_markers, wake_markers, 
                idx_wake_markers*sizeof(VortexMarker_t), cudaMemcpyHostToDevice) );

    // Phase 3: parallel computing


    // Phase 4: retrieve data dev_wake_markers from GPU to wake_markers
    HANDLE_ERROR( cudaMemcpy(wake_markers, dev_wake_markers,
                idx_wake_markers*sizeof(VortexMarker_t), cudaMemcpyDeviceToHost) );

    // Phase 5: GPU computed, distribute the memory to every rotor wake states
    idx_wake_markers = 0;
    for(idx_robot = 0; idx_robot < robots->size(); idx_robot++) {
        for (idx_rotor = 0; idx_rotor < robots->at(idx_robot)->wakes.size(); idx_rotor++) {
            std::copy(&wake_markers[idx_wake_markers],
                &wake_markers[idx_wake_markers+robots->at(idx_robot)->wakes[idx_rotor]->wake_state.size()], robots->at(idx_robot)->wakes[idx_rotor]->wake_state.data());
            idx_wake_markers += robots->at(idx_robot)->wakes[idx_rotor]->wake_state.size();
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
    cudaDeviceProp prop;
    int count; // number of devices
    HANDLE_ERROR( cudaGetDeviceCount(&count) );
    for (int i = 0; i < count; i++) {// print out info of all graphic cards
        HANDLE_ERROR( cudaGetDeviceProperties(&prop, i) );
        printf("======== Card %d ========\n", i+1);
        printf("Graphic card name: %s\n", prop.name);
        printf("Compute Capability: %d.%d\n", prop.major, prop.minor);
        printf("Total global memory: %ld MByte\n", prop.totalGlobalMem/1024/1024);
        printf("Total constant memoty: %ld kByte\n", prop.totalConstMem/1024);
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

    // allocate a page-locked host memory containing all of the marker states
    int max_num_markers = 0;
    for(int idx_robot = 0; idx_robot < robots->size(); idx_robot++) {
        for (int idx_rotor = 0; idx_rotor < robots->at(idx_robot)->wakes.size(); idx_rotor++) {
            max_num_markers += robots->at(idx_robot)->wakes[idx_rotor]->max_markers;
        }
    }// traversed all rotor wakes and got total max number of markers
    HANDLE_ERROR( cudaHostAlloc((void**)&wake_markers, 
        max_num_markers*sizeof(*wake_markers), cudaHostAllocDefault) );

    // allocate device memory as big as the host's
    HANDLE_ERROR( cudaMalloc((void**)&dev_wake_markers, max_num_markers*sizeof(*dev_wake_markers)) );
}

/* close GPU computation */
void WakesFinish(void)
{
    // free device memory
    HANDLE_ERROR( cudaFree(dev_wake_markers) );
    // free host memory
    HANDLE_ERROR( cudaFreeHost(wake_markers) );
}

/* End of file wake.cu */
