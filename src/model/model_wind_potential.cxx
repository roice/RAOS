/*
 * Potential flow field model
 *
 * Author:  Roice Luo
 * Date:    2017-07-26  create this file
 */

#include "model_wind_potential.h"

model_wind_potential_c::model_wind_potential_c(void)
{
}

void model_wind_potential_c::set_mean_vel(float *vel)
{
    mean_wind_vel[0] = vel[0];
    mean_wind_vel[1] = vel[1];
    mean_wind_vel[2] = vel[2];
}

void model_wind_potential_c::update(void)
{
}
