#ifndef RAOS_MATH_COLORED_NOISE_H
#define RAOS_MATH_COLORED_NOISE_H

typedef struct {
    float damping;
    float bandwidth;
    float G;
} Colored_Noise_Params_t;

typedef struct {
    float x[2];
} Colored_Noise_State_t;

float colored_noise(Colored_Noise_Params_t* params, Colored_Noise_State_t* state, float random, float dt);

#endif
