#include <string.h>
#include <ctime>
#include <random>
#include "model/environment.h"

SimEnvInfo::SimEnvInfo(float delta_t)
{
    dt = delta_t;
#ifdef ENV_WIND_WEIBULL
    random_generator = new std::default_random_engine;
    weibull_dist_wind[0] = new std::weibull_distribution<float>(100, 0.3);
    weibull_dist_wind[1] = new std::weibull_distribution<float>(100, 0.3);
    weibull_dist_wind[2] = new std::weibull_distribution<float>(100, 0.3);
#endif

#ifdef ENV_WIND_CN
    wind_cn_params.damping = 0.3;
    wind_cn_params.bandwidth = 0.05;
    wind_cn_params.G = 10.0;
    wind_cn_state = (Wind_Colored_Noise_State_t*)malloc(sizeof(Wind_Colored_Noise_State_t)*3);
    memset(wind_cn_state, 0, sizeof(Wind_Colored_Noise_State_t)*3); // 3 components
    std::srand(std::time(0)); // use current time as seed for random generator
#endif
}

#ifdef ENV_WIND_CN
float colored_noise(Wind_Colored_Noise_Params_t* params, Wind_Colored_Noise_State_t* state, float dt) {
    // sample from standard normal
    float u = (float)std::rand() / (float)RAND_MAX - 0.5;
    // init local params
    float dx[2] = {0};
    dx[0] = state->x[1];
    dx[1] = -2*params->damping*params->bandwidth*dx[0] + params->bandwidth*params->bandwidth*(params->G*u - state->x[0]);
    state->x[1] += dx[1] * dt;
    state->x[0] += state->x[1] * dt;
    return state->x[0];
}
#endif

void SimEnvInfo::measure_wind(float* pos, float* wind)
{
#ifdef ENV_WIND_WEIBULL
    wind[0] = (*weibull_dist_wind[0])(*random_generator);
    wind[1] = (*weibull_dist_wind[1])(*random_generator);
    wind[2] = (*weibull_dist_wind[2])(*random_generator);
    printf("SimEnvInfo: generated wind = [ %f, %f, %f ]\n", wind[0], wind[1], wind[2]);
#endif

#ifdef ENV_WIND_CN
    wind[0] = colored_noise(&wind_cn_params, &wind_cn_state[0], dt) + 2.0;
    wind[1] = colored_noise(&wind_cn_params, &wind_cn_state[1], dt) + 0.0;
    wind[2] = colored_noise(&wind_cn_params, &wind_cn_state[2], dt) + 0.0;
    //printf("SimEnvInfo: generated wind = [ %f, %f, %f ]\n", wind[0], wind[1], wind[2]);
#endif
}

void SimEnvInfo::destroy(void)
{
#ifdef ENV_WIND_WEIBULL
    for (int i = 0; i < 3; i++)
        delete weibull_dist_wind[i];
    delete random_generator;
#endif

#ifdef ENV_WIND_CN
    free(wind_cn_state);
#endif
}
