#ifndef MODEL_WIND_H
#define MODEL_WIND_H

void model_wind_register(RAOS_model_t *model);
bool model_wind_get_vel_at_pos(float *pos, float *vel);
void model_wind_unregister(void);

#endif
