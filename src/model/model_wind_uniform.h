#ifndef MODEL_WIND_UNIFORM_H
#define MODEL_WIND_UNIFORM_H

class model_wind_uniform_c {
    public:
        model_wind_uniform_c(void);
        void update(void);
        float wind_vel[3];
};

#endif
