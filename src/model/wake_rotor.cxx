/*
 * single-rotor wake model running on GPU
 *      Free vortex method
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-03-02 create this file (RAOS)
 *       2016-03-08 CPU too slow, modified to GPU
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h> // drand48 and srand48 on Linux
#include <string.h> // memset
#include "cblas.h" // CBLAS for vector arithmetic
#include "model/wake_rotor.h"

#define PI 3.14159265358979323846

void RotorWake::init(void) // rotor wake initialization
{// by far config and rotor_state should be artificially configured

    // init vortex markers state
    max_markers = int(360.0*config.rounds/10.0)+1; // calculate max lagrangian markers of a vortex filament, 10.0 degree is an arbitrary number
    wake_state.reserve(rotor_state.frame.n_blades*(max_markers+10)); // 10 is an arbitrary number, can be num>=1
    
    // release first pair of marker at the tips
    marker_release();
}

void RotorWake::maintain(void) 
{/* marker maintainance */
    
    // release new markers
    marker_release();
    
    // remove old markers
    if (wake_state.size() > max_markers) {
        for (int i = 0; i < rotor_state.frame.n_blades; i++)
            wake_state.erase(wake_state.begin());
    }
}

void RotorWake::marker_release(void) {

    VortexMarker_t new_marker;
    float p_marker[3] = {rotor_state.frame.radius, 0, 0};

    // clear velocity
    memset(new_marker.vel, 0, sizeof(new_marker.vel));

    // calculate the tip vortex circulation: Gamma
    new_marker.Gamma = 1; // tip vortex circulation

    for (int i = 0; i < rotor_state.frame.n_blades; i++) {
        // calculate the position of this marker     
        memcpy(new_marker.pos, rotor_state.pos, sizeof(new_marker.pos));
        rotate_vector(p_marker, new_marker.pos, 360.0/rotor_state.frame.n_blades*i+rotor_state.psi+rotor_state.attitude[0], rotor_state.attitude[1], rotor_state.attitude[2]);
        // push to wake state array
        wake_state.push_back(new_marker);
    }

    // update blade azimuth
    rotor_state.psi += config.dt*rotor_state.Omega*180/PI;
    if (rotor_state.psi >= 360.0)
        rotor_state.psi -= 360.0;
}

// Constructor
RotorWake::RotorWake(void)
{
    // init configurations
    config.dt = 0.001; // 10 ms
    config.rounds = 20; // 20 rounds

    // init rotor state
    rotor_state.frame.radius = 0.1; // meter
    rotor_state.frame.n_blades = 2; // two-blade
    memset(rotor_state.pos, 0, sizeof(rotor_state.pos));
    memset(rotor_state.attitude, 0, sizeof(rotor_state.attitude));
    rotor_state.Omega = 50*2*PI; // rad/s
    rotor_state.psi = 0;
    
    max_markers = 1000;
}

/* End of file wake_rotor.cxx */
