/*
 * quad-rotor wake model running on CPU
 *      Free vortex method
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-03-04 create this file (RAOS)
 */

#include "model/qrmod.h"  // for qrstate_t

class QRWake {
    public:
        void init(qrstate_t); // quad rotor wake init
        void update(void); // quad rotor wake update
        RotorWake* rotor_wake[4];
};

