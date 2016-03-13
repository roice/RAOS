/*
 * single-rotor wake model running on GPU
 *      Free vortex method
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-03-02 create this file (RAOS)
 *       2016-03-08 CPU too slow, modified to GPU
 */

#ifndef WAKE_ROTOR_H
#define WAKE_ROTOR_H

#include <vector>

typedef struct
{
    float radius; // propeller radius
    int n_blades; // number of blades
} RotorFrame_t; // mechanical frame (constant)

typedef struct {
    float pos[3];	/* position coordinate (earth axis x), volatile */
    float attitude[3]; // [yaw, pitch, roll]
    float Omega; // rotation angular speed, volatile
    float psi; // blade azimuth, [0, 360), volatile
    RotorFrame_t frame; // const
}RotorState_t;

typedef struct {
    float pos[3]; // 3D position of this marker
    float vel[3]; // 3D velocity of this marker
    float Gamma; // circulation of i-th segment (i-th marker to (i+1)-th marker)
    float r; // vortex core radius
}VortexMarker_t;

typedef struct {
    float dt; // delta time to release/maintain marker
    float rounds; // number of revolutions (number of vortex rings to maintain) 
}RotorWakeConfig_t; // const since sim init

class RotorWake {
    public:
        RotorWake(void); // constructor
        void init(void); // rotor wake init
        void maintain(void); // marker release & remove, to maintain a fixed length of vortex filament
        std::vector<VortexMarker_t>** wake_state; // wake_state[i] is the pointer of a std::vector, which contains the markers of a whole filament
        RotorWakeConfig_t config; // configures of rotor wake simulation
        RotorState_t rotor_state;
        int max_markers;

    private:
        void marker_release(void); 
};

/* rotate a vector to given euler angles */
void rotate_vector(const float*, float*, float, float, float);

#endif
/* End of file wake_rotor.h */
