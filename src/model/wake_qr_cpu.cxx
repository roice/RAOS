/*
 * quad-rotor wake model running on CPU
 *      Free vortex method
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-03-02 create this file (RAOS)
 */

#include <string.h>
#include "cblas.h"
#include "model/qrmod.h"
#include "model/wake_rotor_cpu.h" // wake of a single rotor
#include "model/wake_qr_cpu.h"
#include <stdio.h>

static void calculate_rotor_pos(const qrstate_t* qrstate, float* rpos1, float* rpos2, float* rpos3, float* rpos4) {
    // init rotor pos vector
    rpos1[0] = qrstate->x;
    rpos1[1] = qrstate->y;
    rpos1[2] = qrstate->z;
    memcpy(rpos2, rpos1, 3*sizeof(float));
    memcpy(rpos3, rpos1, 3*sizeof(float));
    memcpy(rpos4, rpos1, 3*sizeof(float));

    // calculate rotor pos
    float v[3] = {qrstate->frame.size/2.0, 0.0, 0.0};
    rotate_vector(v, rpos1, qrstate->psi, qrstate->theta, qrstate->phi);
    rotate_vector(v, rpos2, 90+qrstate->psi, qrstate->theta, qrstate->phi);
    rotate_vector(v, rpos3, 180+qrstate->psi, qrstate->theta, qrstate->phi);
    rotate_vector(v, rpos4, 270+qrstate->psi, qrstate->theta, qrstate->phi);
}

QRWake::QRWake(void)
{
    // create four instances of rotor wake
    for (int i = 0; i < 4; i++)
        rotor_wake[i] = new RotorWake();
    // default value
    config.dpsi = 15; // degree
    config.rounds = 20;

printf("QRWake constructed\n");
fflush(stdout);
}

// before calling init, config should be artificially setted
void QRWake::init(const qrstate_t* qrstate)
{
    /* Init rotor wakes' parameters */
    for (int i = 0; i < 4; i++) {
        // FVM related configures
        rotor_wake[i]->config.dpsi = config.dpsi;
        rotor_wake[i]->config.rounds = config.rounds;
        // prop radius
        rotor_wake[i]->rotor_state.frame.radius = qrstate->frame.prop_radius;
    }
    // position of rotors
    calculate_rotor_pos(qrstate, rotor_wake[0]->rotor_state.pos, rotor_wake[1]->rotor_state.pos, rotor_wake[2]->rotor_state.pos, rotor_wake[3]->rotor_state.pos);

//printf("rotor_pos_1 = {%f, %f, %f}\n", rotor_wake[3]->rotor_state.pos[0], rotor_wake[3]->rotor_state.pos[1], rotor_wake[3]->rotor_state.pos[2]);
//fflush(stdout);

    // rotation speeds of rotors
    rotor_wake[0]->rotor_state.Omega = qrstate->a1;
    rotor_wake[1]->rotor_state.Omega = qrstate->a2;
    rotor_wake[2]->rotor_state.Omega = qrstate->a3;
    rotor_wake[3]->rotor_state.Omega = qrstate->a4;

//printf("rotation speed = {%f, %f, %f, %f}\n", rotor_wake[0]->rotor_state.Omega, rotor_wake[1]->rotor_state.Omega, rotor_wake[2]->rotor_state.Omega, rotor_wake[3]->rotor_state.Omega);
//fflush(stdout);


    /* Init rotor wakes */
    for(int i = 0; i < 4; i++)
        rotor_wake[i]->init(qrstate);

    /*
     * TODO: 
     * compute vortex filaments when rotors rotate at different speed.
     * The rotors have different dt...*/
    // delta time
    dt = config.dpsi/rotor_wake[0]->rotor_state.Omega;
}

void QRWake::update(const qrstate_t* qrstate)
{
    /* Step 1: Update rotors' state */
    // update rotors' pos
    calculate_rotor_pos(qrstate,
            rotor_wake[0]->rotor_state.pos,
            rotor_wake[1]->rotor_state.pos,
            rotor_wake[2]->rotor_state.pos,
            rotor_wake[3]->rotor_state.pos);

//printf("rotor_pos_1 = {%f, %f, %f}\n", rotor_wake[3]->rotor_state.pos[0], rotor_wake[3]->rotor_state.pos[1], rotor_wake[3]->rotor_state.pos[2]);
//fflush(stdout);


    // update props' rotation speeds
    rotor_wake[0]->rotor_state.Omega = qrstate->a1;
    rotor_wake[1]->rotor_state.Omega = qrstate->a2;
    rotor_wake[2]->rotor_state.Omega = qrstate->a3;
    rotor_wake[3]->rotor_state.Omega = qrstate->a4;


//printf("rotation speed = {%f, %f, %f, %f}\n", rotor_wake[0]->rotor_state.Omega, rotor_wake[1]->rotor_state.Omega, rotor_wake[2]->rotor_state.Omega, rotor_wake[3]->rotor_state.Omega);
//fflush(stdout);

    /* Step 2: Update rotor vortex filaments */
    int n_b; // number of blades a rotor has
    int n_m; // number of markers a tip vortex filament has
    for(int idx_r = 0; idx_r < 4; idx_r++)
    {// for each rotor
        n_b = rotor_wake[idx_r]->rotor_state.frame.n_blades;
        n_m = rotor_wake[idx_r]->wake_state.size()/n_b;

//printf("n_b = %d, n_m = %d\n", n_b, n_m);
//fflush(stdout);

        for(int idx_b = 0; idx_b < n_b; idx_b++)
        {// for each blade
            for(int idx_m = 0; idx_m < n_m; idx_m++)
            {// for each marker
                // calculate the vel of this marker
                CalculateInducedVelocityOfMarker(
                    rotor_wake[idx_r]->wake_state.at(idx_m*n_b+idx_b).vel,
                    idx_r, idx_b, idx_m,
                    rotor_wake, 4);

//printf("%f\n", rotor_wake[idx_r]->wake_state.at(idx_m*n_b+idx_b).vel[2]);
//   fflush(stdout);

                // update postion of this marker
                cblas_saxpy(3, dt,
                    rotor_wake[idx_r]->wake_state.at(idx_m*n_b+idx_b).vel, 1,
                    rotor_wake[idx_r]->wake_state.at(idx_m*n_b+idx_b).pos, 1); // Euler, 1-order precision

//printf("%f\n", rotor_wake[idx_r]->wake_state.at(idx_m*n_b+idx_b).vel[2]);
 //   fflush(stdout);

            }
        }
    }

    /* Step 3: Maintain rotor wakes */
    for(int i = 0; i < 4; i++)
        rotor_wake[i]->maintain(qrstate);

    /*
     * TODO: 
     * compute vortex filaments when rotors rotate at different speed.
     * The rotors have different dt...*/
    // update delta time
    dt = config.dpsi/rotor_wake[0]->rotor_state.Omega;
}
