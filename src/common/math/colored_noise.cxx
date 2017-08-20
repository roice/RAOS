#include "colored_noise.h"

/*
 * mean of rand_normal is 0
 */
float colored_noise(Colored_Noise_Params_t* params, Colored_Noise_State_t* state, float rand_normal, float dt) {
    float u = rand_normal;
    // init local params
    float dx[2] = {0};
    dx[0] = state->x[1];
    dx[1] = -2*params->damping*params->bandwidth*dx[0] + params->bandwidth*params->bandwidth*(params->G*u - state->x[0]);
    state->x[1] += dx[1] * dt;
    state->x[0] += state->x[1] * dt;
    return state->x[0];
}
