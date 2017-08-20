#ifndef MODEL_WIND_UNIFORM_H
#define MODEL_WIND_UNIFORM_H

#include <random>
#include "common/math/colored_noise.h"

class model_wind_uniform_c {
    public:
        model_wind_uniform_c(float);
        void set_vel(float*);
        void update(void);
        void get_vel(float*);
        void destroy(void);
    private:
        float dt;
        float wind_vel[3];
        float wind_mean_vel[3];
        std::default_random_engine *rand_generator[3];
        std::normal_distribution<float> *rand_gaussian[3];
        Colored_Noise_Params_t wind_cn_params;
        Colored_Noise_State_t *wind_cn_state;
};

#endif
