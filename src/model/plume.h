/*
 * plume model
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-26 create this file (RAOS)
 */
#ifndef PLUME_H
#define PLUME_H

#include <vector>

#define USE_FILAMENT_MODEL // use filament plume model

void plume_init(void);
void plume_update(void);

#if defined(USE_FILAMENT_MODEL)
#define MAX_NUM_PUFFS 1000
typedef struct {
    float pos[3];
    float vel[3];
    float r;
}FilaState_t; // struct type of the state of a single filament

std::vector<FilaState_t>* plume_get_fila_state(void);
#endif

#endif
/* End of plume.h */
