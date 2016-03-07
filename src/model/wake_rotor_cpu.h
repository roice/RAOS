/*
 * single-rotor wake model running on CPU
 *      Free vortex method
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-03-02 create this file (RAOS)
 */

#ifndef WAKE_ROTOR_CPU_H
#define WAKE_ROTOR_CPU_H

#include <vector>

typedef struct
{
    float radius; // propeller radius
    int n_blades; // number of blades
} RotorFrame_t; // mechanical frame (constant)

typedef struct {
    float roll;	/* roll angle (Euler angle x) */
  	float pitch;	/* pitch angle (Euler angle y) */
  	float yaw;	/* yaw angle (Euler angle z) */
    float x;	/* position coordinate (earth axis x) */
  	float y;	/* position coordinate (earth axis y) */
  	float z;	/* position coordinate (earth axis z) */
    float Omega; // rotation angular speed
    float psi; // blade azimuth, [0, 360)

    RotorFrame_t frame;
}RotorState_t;

typedef struct {
    float pos[3]; // 3D position of this marker
    float vel[3]; // 3D velocity of this marker
    float Gamma; // circulation of i-th segment (i-th marker to (i+1)-th marker)
    float r; // vortex core radius
}VortexMarker_t;

typedef struct {
    float dpsi; // delta_psi, interval_angle (reference)
    float rounds; // number of revolutions (number of vortex rings to maintain) 
}RotorWakeConfig_t;

class RotorWake {
    public:
        RotorWake(void); // constructor
        void init(void); // rotor wake init
        void update(void); // rotor wake update

        std::vector<VortexMarker_t> wake_state; // state of vortex markers
        RotorWakeConfig_t config; // configures of rotor wake simulation
        RotorState_t rotor_state;
    private:
        void marker_release(void);

        float dt; // delta time (volatile, change according to psi and Omega)
        int max_markers; // maximum markers
};

#endif
