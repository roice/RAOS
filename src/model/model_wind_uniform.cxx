/*
 * Uniform wind field model
 *
 * Author:  Roice Luo
 * Date:    2017-07-24  create this file
 */

#include "model/model_wind_uniform.h"

model_wind_uniform_c::model_wind_uniform_c(void)
{
}

void model_wind_uniform_c::set_vel(float *vel)
{
    wind_vel[0] = vel[0];
    wind_vel[1] = vel[1];
    wind_vel[2] = vel[2];
}

void model_wind_uniform_c::update(void)
{
}

void model_wind_uniform_c::get_vel_at_pos(float *pos, float *vel)
{
    vel[0] = 0.5;
    vel[1] = 0;
    vel[2] = 0;
}
