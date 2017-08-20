/*
 * Functions of managing wind models
 *
 * Author:  Roice Luo
 * Date:    2017-08-10  create this file
 */

#include <stdio.h>
#include <thrust/host_vector.h>
#include "common/RAOS_types.h"
#include "model/model_wind_uniform.h"
#include "model/model_wind_potential.h"


RAOS_model_t    model_wind = {RAOS_MODEL_WIND_UNIFORM, NULL};

void model_wind_register(RAOS_model_t *model)
{
    model_wind.type = model->type;
    model_wind.ptr = model->ptr;
}

bool model_wind_get_vel_at_pos(float *pos, float *vel)
{
    if (!model_wind.ptr)
        return false;

    switch (model_wind.type)
    {
        case RAOS_MODEL_WIND_UNIFORM:
        {
            ((model_wind_uniform_c*)model_wind.ptr)->get_vel(vel);
            break;
        }
        default:
            break;
    }

    return true;
}

/*
 * ptr_arr is a pointer of an array of vectors
 * ptr_arr[0]   pointer of vector pos_x
 * ptr_arr[1]   pointer of vector pos_y
 * ptr_arr[2]   pointer of vector pos_z
 * ptr_arr[3]   pointer of vector vel_x
 * ptr_arr[4]   pointer of vector vel_y
 * ptr_arr[5]   pointer of vector vel_z
 */
bool model_wind_get_batch_vel_at_pos(thrust::host_vector<float>** ptr_arr_vec)
{
    if (!model_wind.ptr)
        return false;
    switch (model_wind.type)
    {
        case RAOS_MODEL_WIND_UNIFORM:
        {
            float vel[3];
            ((model_wind_uniform_c*)model_wind.ptr)->get_vel(vel);

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < (int)(ptr_arr_vec[i+3]->size()); j++)
                    (*ptr_arr_vec[i+3])[j] = vel[i];
            return true;
        }
        default:
            break;
    }
    return false;
}

void model_wind_unregister(void)
{
    model_wind.type = RAOS_MODEL_WIND_UNIFORM;
    model_wind.ptr = NULL;
}
