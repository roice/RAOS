#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <random>

#ifndef ENV_WIND_CN
#define ENV_WIND_CN
#endif

#ifdef ENV_WIND_CN
typedef struct {
    float damping;
    float bandwidth;
    float G;
} Wind_Colored_Noise_Params_t;

typedef struct {
    float x[2];
} Wind_Colored_Noise_State_t;
#endif

class SimEnvInfo {
    public:
        SimEnvInfo(float);
        void measure_wind(float*, float*);
        void destroy(void);
    private:
        float dt;
#ifdef ENV_WIND_WEIBULL
        std::default_random_engine* random_generator;
        std::weibull_distribution<float>* weibull_dist_wind[3];
#endif
#ifdef ENV_WIND_CN
        Wind_Colored_Noise_Params_t wind_cn_params;
        Wind_Colored_Noise_State_t *wind_cn_state;
#endif
};

#endif
