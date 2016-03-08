/*
 * quad-rotor wake model running on CPU
 *      Free vortex method
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-03-04 create this file (RAOS)
 */
#ifndef WAKE_QR_CPU_H
#define WAKE_QR_CPU_H


#include "model/qrmod.h"  // for qrstate_t
#include "model/wake_rotor_cpu.h" // for RotorWake class type

typedef struct {
    float dpsi; // delta_psi, interval_angle (reference)
    float rounds; // number of revolutions (number of vortex rings to maintain)
}QRWakeConfig_t;

class QRWake {
    public:
        QRWake(void); // constructor
        void init(const qrstate_t*); // quad rotor wake init
        void update(const qrstate_t*); // quad rotor wake update
        RotorWake* rotor_wake[4];
        QRWakeConfig_t config;
        float dt;
};

#endif
