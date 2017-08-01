#ifndef MODEL_WIND_POTENTIAL_H
#define MODEL_WIND_POTENTIAL_H

class model_wind_potential_c {
    public:
        model_wind_potential_c(void);
        void update(void);
        float mean_wind_vel[3];
};

#endif
