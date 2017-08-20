#ifndef MODEL_PLUME_FARRELL_H
#define MODEL_PLUME_FARRELL_H

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

#define MODEL_PLUME_FARRELL_MAX_NUM_PUFFS   1000
#define MODEL_PLUME_FARRELL_MAX_PUFF_SIZE   1.0     // m
#define MODEL_PLUME_FARRELL_MIN_PUFF_SIZE   0.01    // cm

class model_plume_farrell_c {
    public:
        model_plume_farrell_c(float, float, float, float, int, float);
        void update(void);
        void destroy(void);
        thrust::host_vector<float>** get_state(void);
    private:
        float dt;
        float puffs_to_release;
        // parameters
        float _source_pos[3];
        float _lambda;
        int   _pps;
        // internal states
        int _idx_puff;
        /* pos (3) vel (3) r (1) dt(1) */
        thrust::host_vector<float> *h_puffs[8];
        thrust::device_vector<float> *d_puffs[8];
};

#endif
