#ifndef MODEL_WIND_UNIFORM_H
#define MODEL_WIND_UNIFORM_H

class model_wind_uniform_c {
    public:
        model_wind_uniform_c(void);
        void set_vel(float*);
        void update(void);
        void get_vel_at_pos(float*, float*);
    private:
        float wind_vel[3];
};

#endif
