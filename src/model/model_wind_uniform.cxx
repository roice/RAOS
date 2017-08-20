/*
 * Uniform wind field model
 *
 * Author:  Roice Luo
 * Date:    2017-07-24  create this file
 */

#include <random>
#include <ctime>
#include <string.h>
#include "model/model_wind_uniform.h"
#include "common/math/colored_noise.h"

model_wind_uniform_c::model_wind_uniform_c(float dtime)
{
    dt = dtime;

    // random generator
    for (int i = 0; i < 3; i++) {
        rand_generator[i] = new std::default_random_engine;
        rand_generator[i]->seed(std::time(0));
        rand_gaussian[i] = new std::normal_distribution<float>(0, 0.5);
    }

    // default mean vel
    wind_mean_vel[0] = 0.5;
    wind_mean_vel[1] = 0.;
    wind_mean_vel[2] = 0.;
    
    // colored noise init
    wind_cn_params.damping = 0.3;
    wind_cn_params.bandwidth = 0.05;
    wind_cn_params.G = 10.0;
    wind_cn_state = (Colored_Noise_State_t*)malloc(sizeof(Colored_Noise_State_t)*3);
    memset(wind_cn_state, 0, sizeof(Colored_Noise_State_t)*3); // 3 components
}

void model_wind_uniform_c::set_vel(float *vel)
{
    memcpy(wind_vel, vel, 3*sizeof(float));
}

void model_wind_uniform_c::update(void)
{
    for (int i = 0; i < 3; i++)
        wind_vel[i] = wind_mean_vel[i] + colored_noise(&wind_cn_params, &wind_cn_state[i], (*rand_gaussian[i])(*rand_generator[i]), dt);
}

void model_wind_uniform_c::get_vel(float *vel)
{
    memcpy(vel, wind_vel, 3*sizeof(float));
}

void model_wind_uniform_c::destroy(void)
{
    for (int i = 0; i < 3; i++) {
        delete  rand_generator[i];
        delete  rand_gaussian[i];
    }
    delete  wind_cn_state;
}
