/*
 * single-rotor wake model running on CPU
 *      Free vortex method
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-03-02 create this file (RAOS)
 */

#ifndef WAKE_ROTOR_CPU_H
#define WAKE_ROTOR_CPU_H

typedef struct {
    float x;
    float y;
    float z;
    float r; // vortex core radius
}VortexMarker_t;

#endif
