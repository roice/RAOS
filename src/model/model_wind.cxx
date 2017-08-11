/*
 * Functions of managing wind models
 *
 * Author:  Roice Luo
 * Date:    2017-08-10  create this file
 */

#include <stdio.h>

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
            ((model_wind_uniform_c*)model_wind.ptr)->get_vel_at_pos(pos, vel);
            break;
        }
        default:
            break;
    }

    return true;
}

void model_wind_unregister(void)
{
    model_wind.type = RAOS_MODEL_WIND_UNIFORM;
    model_wind.ptr = NULL;
}
