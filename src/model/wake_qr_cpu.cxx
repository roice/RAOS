/*
 * quad-rotor wake model running on CPU
 *      Free vortex method
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-03-02 create this file (RAOS)
 */

#include "model/wake_rotor_cpu.h" // wake of a single rotor
#include "model/wake_qr_cpu.h"



void QRWake::init(qrstate_t qrstate)
{
    // calculate each rotor's position and attitude

    // create four instances of rotor wake
    for (int i = 0; i < 4; i++)
        rotor_wake[i] = new RotorWake();
}




