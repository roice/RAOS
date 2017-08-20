/*
 * 3D Robots Drawing
 *          using OpenGL GLUT
 *
 * This file contains stuff for drawing the robots for 3D
 * Robot Active Olfaction using OpenGL GLUT.
 * The declarations of the classes or functions are written in 
 * file draw_robots.h, which is included by DrawScene.h
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-03-09 create this file
 */

#include GL_HEADER
#include <vector>
#include "RAOS_config.h"
#include "model/RAOS_model.h"
#include "model/model_robot_microbee.h"
#include "common/RAOS_types.h"
#include "ui/draw/draw_qr.h"

void draw_robots(void)
{
    RAOS_config_t *configs = RAOS_config_get_settings();

    for (int idx_robot = 0; idx_robot < configs->arena.num_robots; idx_robot++)
    {// draw every robot

        /* draw robot according to its type, configures... */
        if (configs->robot[idx_robot].model_name == "MicroBee")
        {// draw quadrotor
            int model_order = RAOS_model_list_find_robot_by_type_and_id(RAOS_MODEL_ROBOT_MICROBEE, idx_robot);
            if (model_order < 0)
                continue;
            float *pos = ((model_robot_microbee_c*)(RAOS_model_get_list()->at(model_order).ptr))->pos;
            float *att = ((model_robot_microbee_c*)(RAOS_model_get_list()->at(model_order).ptr))->att;
            draw_qr(pos, att, 0.5, 0.15);
        }
    }
}

/* End of draw_robots.cxx */
