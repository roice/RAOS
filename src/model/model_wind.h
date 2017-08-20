#ifndef MODEL_WIND_H
#define MODEL_WIND_H

#include <thrust/host_vector.h>
#include "RAOS_model.h"

void model_wind_register(RAOS_model_t *model);
bool model_wind_get_vel_at_pos(float *pos, float *vel);
bool model_wind_get_batch_vel_at_pos(thrust::host_vector<float>**);
void model_wind_unregister(void);

#endif
