/*
 * Farrell plume model
 *
 * Author:  Roice Luo
 * Date:    2017-07-26  create this file
 */

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/random.h>
#include <thrust/for_each.h>
#include <thrust/iterator/zip_iterator.h>
#include "model/model_plume_farrell.h"
#include "model/model_wind.h"


template <typename T1, typename T2, typename T3>
struct  update_puff_state
{
    const T1 lambda;
    const T2 dt;
    const T3 count;
    update_puff_state(T1 _lambda, T2 _dt, T3 _count):lambda(_lambda),dt(_dt),count(_count) {}

    /*  PuffState    <0>     pos_x
        PuffState    <1>     pos_y
        PuffState    <2>     pos_z
        PuffState    <3>     vel_x
        PuffState    <4>     vel_y
        PuffState    <5>     vel_z
        PuffState    <6>     r
        PuffState    <7>     real dt
    */
    template <typename PuffState>
    __host__ __device__
    void operator()(PuffState state) const {
        float pos[3], vel[3], r, r_dt;
        int idx;
        thrust::tie(pos[0], pos[1], pos[2], vel[0], vel[1], vel[2], r, r_dt, idx) = state;

        // generate random speed to simulate mid-scale turbulence
        thrust::default_random_engine rng;
        thrust::normal_distribution<float> dist(0, lambda);
        rng.discard(3*(count*MODEL_PLUME_FARRELL_MAX_NUM_PUFFS+idx));

        // update position
        for (int i = 0; i < 3; i++)
            pos[i] += (vel[i] + dist(rng))*r_dt;

        // update size
        r += 0.0001;

        // save results
        thrust::get<0>(state) = pos[0];
        thrust::get<1>(state) = pos[1];
        thrust::get<2>(state) = pos[2];
        thrust::get<6>(state) = r;
        thrust::get<7>(state) = dt;
    }
};

model_plume_farrell_c::model_plume_farrell_c(
        float source_pos_x,
        float source_pos_y,
        float source_pos_z,
        float lambda,
        int parcels_per_sec,
        float dtime
        )
{
    dt = dtime;
    // save parameters
    _source_pos[0] = source_pos_x;
    _source_pos[1] = source_pos_y;
    _source_pos[2] = source_pos_z;
    _lambda = lambda;
    _pps = parcels_per_sec > 1.0 / dt ? parcels_per_sec : 1.0 / dt;

    // allocate memory
    for (int i = 0; i < 8; i++) {
        h_puffs[i] = new thrust::host_vector<float>(MODEL_PLUME_FARRELL_MAX_NUM_PUFFS);
        d_puffs[i] = new thrust::device_vector<float>(MODEL_PLUME_FARRELL_MAX_NUM_PUFFS);
    }
    // initialize puffs
    _idx_puff = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < MODEL_PLUME_FARRELL_MAX_NUM_PUFFS; j++)
            (*h_puffs[i])[j] = _source_pos[i];
    for (int j = 0; j < MODEL_PLUME_FARRELL_MAX_NUM_PUFFS; j++) {
        (*h_puffs[3])[j] = 0;
        (*h_puffs[4])[j] = 0;
        (*h_puffs[5])[j] = 0;
        (*h_puffs[6])[j] = MODEL_PLUME_FARRELL_MAX_PUFF_SIZE;
        (*h_puffs[7])[j] = dt;
    }
    // initialize puff releasing count
    puffs_to_release = 0;
}

void model_plume_farrell_c::update(void)
{
    static unsigned int count = 0;

/* step 1: update velocities of puffs */
    // update velocity of puffs
    model_wind_get_batch_vel_at_pos(h_puffs);

/* step 2: update positions of puffs */
    // copy memory from host to device
    for (int i = 0; i < 8; i++)
        thrust::copy(h_puffs[i]->begin(), h_puffs[i]->end(), d_puffs[i]->begin()); 

    // update position of puffs
    thrust::for_each(
            thrust::make_zip_iterator(thrust::make_tuple(
                    d_puffs[0]->begin(),
                    d_puffs[1]->begin(),
                    d_puffs[2]->begin(),
                    d_puffs[3]->begin(),
                    d_puffs[4]->begin(),
                    d_puffs[5]->begin(),
                    d_puffs[6]->begin(),
                    d_puffs[7]->begin(),
                    thrust::make_counting_iterator(0)
                    )),
            thrust::make_zip_iterator(thrust::make_tuple(
                    d_puffs[0]->end(),
                    d_puffs[1]->end(),
                    d_puffs[2]->end(),
                    d_puffs[3]->end(),
                    d_puffs[4]->end(),
                    d_puffs[5]->end(),
                    d_puffs[6]->end(),
                    d_puffs[7]->end(),
                    thrust::make_counting_iterator(MODEL_PLUME_FARRELL_MAX_NUM_PUFFS)
                    )),
            update_puff_state<float, float, unsigned int>(_lambda, dt, count++)
            );

    // copy memory from device to host
    for (int i = 0; i < 8; i++)
        thrust::copy(d_puffs[i]->begin(), d_puffs[i]->end(), h_puffs[i]->begin());
    
/* step 3: puff maintenance */
    puffs_to_release = dt * _pps;
    for (int i = 1; i < puffs_to_release; i++) {
        // release new puff
        (*h_puffs[0])[_idx_puff] = _source_pos[0];
        (*h_puffs[1])[_idx_puff] = _source_pos[1];
        (*h_puffs[2])[_idx_puff] = _source_pos[2];
        (*h_puffs[6])[_idx_puff] = MODEL_PLUME_FARRELL_MIN_PUFF_SIZE;
        (*h_puffs[7])[_idx_puff++] = dt - (float)i / (float)_pps;
        if (_idx_puff >= MODEL_PLUME_FARRELL_MAX_NUM_PUFFS)
            _idx_puff = 0;
    }
}

thrust::host_vector<float>** model_plume_farrell_c::get_state(void)
{
    return h_puffs;
}

void model_plume_farrell_c::destroy(void)
{
    // free memory
    for (int i = 0; i < 8; i++) {
        delete h_puffs[i];
        delete d_puffs[i];
    }
}
