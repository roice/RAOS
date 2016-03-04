/*
 * single-rotor wake model running on CPU
 *      Free vortex method
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-03-02 create this file (RAOS)
 */

#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> // drand48 and srand48 on Linux
#include "wake_rotor_cpu.h"

#define PI 3.14159265358979323846


static float BiotSavartInduction(void) {

    float e = drand48();
    float Gamma = drand48();
    float h = drand48();
    float a = drand48();
    float b = drand48();
    return Gamma/(4*PI);
    //return Gamma/(4*PI)*(h/sqrt(pow(0.01, 4)+pow(h, 4)))*(cos(a)+cos(b))*e;
}

class RotorWake {
    public:
        std::vector<VortexMarker_t> state; // state of vortex markers
        void init(float, float); // rotor wake init
        void update(void); // rotor wake update
    private:
        void marker_release(void)
        {
            VortexMarker_t new_marker;
            state.push_back(new_marker);
        }
};

void RotorWake::init(float Omega, float interval_angle) 
{ // rotor wake initialization
    
    float Gamma = 1; // tip vortex circulation
    float dt = 0.01; // time cost when rotor evolves interval_angle
    // init vortex markers state
    state.reserve(1000);
    // release first pair of marker at the tip
    marker_release();
}

void RotorWake::update(void) {// update markers
    /* Step 1: update existing markers */
    for (int i = 0; i < state.size(); i++) {// for each marker
        // calculate overall flow at this marker's position
        for (int i = 0; i < state.size(); i++) {
            BiotSavartInduction();
        }
    }
    /* Step 2: marker maintainance */
    // release new markers
    marker_release();
    // remove old markers
    if (state.size() > 10000)
        state.erase(state.begin());
}


/**********************************************************
 ***************** TEST ON THIS FILE **********************
 *********************************************************/
#if 1

int main(int argc, char **argv) {
    RotorWake wake;
    wake.init(1, 1);
    while(1) {
        wake.update();
        printf("N = %d\n", wake.state.size());
    }

    return 0;
}

#endif
