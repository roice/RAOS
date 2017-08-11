#ifndef MODEL_WIND_POTENTIAL_H
#define MODEL_WIND_POTENTIAL_H

class model_wind_potential_c {
    public:
        model_wind_potential_c(void);
        void set_mean_vel(float*);
        void update(void);
    private:
        float mean_wind_vel[3];
};

#endif
