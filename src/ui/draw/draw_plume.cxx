/*
 * 3D Plume drawing
 *          using OpenGL GLUT
 *
 * This file contains stuff for drawing plume for 3D
 * Robot Active Olfaction using OpenGL GLUT.
 * The declarations of the classes or functions are written in 
 * file draw_plume.h, which is included by DrawScene.h
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-26 create this file
 */
#include GL_HEADER
#include GLUT_HEADER
#include <vector>
#include "RAOS_config.h"
#include "model/model_plume.h"
#include "model/model_plume_farrell.h"
#include "ui/draw/materials.h"
#include <thrust/host_vector.h>

void draw_plume_farrell(thrust::host_vector<float>** puffs)
{
    if (puffs) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        for (int i = 0; i < MODEL_PLUME_FARRELL_MAX_NUM_PUFFS; i++) // for each filament
        {
            if ((*puffs[6])[i] >= MODEL_PLUME_FARRELL_MAX_PUFF_SIZE)
                continue;
            glPushMatrix(); 
            glTranslatef((*puffs[0])[i], (*puffs[2])[i], -(*puffs[1])[i]);
            glPushAttrib(GL_LIGHTING_BIT);
            //SimMaterial_chlorine(1.0-10*(*puffs[6])[i]);
            SimMaterial_smoke(1.0);
            glutSolidSphere((*puffs[6])[i], 8, 3);
            glPopAttrib();
            glPopMatrix();
        }
        glDisable(GL_BLEND);
    }
}

void draw_plume(void)
{
    RAOS_config_t *configs = RAOS_config_get_settings();

    for (int i = 0; i < configs->arena.num_sources; i++) {
        if (configs->plume[i].model_name == "Farrell")
            draw_plume_farrell((thrust::host_vector<float>**)model_plume_get_state(i));
    }
}
/* End of draw_plume.cxx */
