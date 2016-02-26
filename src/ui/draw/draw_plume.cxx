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
#include <FL/gl.h>
#include <FL/glut.H>
#include <vector>
#include "plume.h"
#include "draw/materials.h"

void draw_plume(void)
{
    std::vector<FilaState_t> *fs = plume_get_fila_state();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (int i = 0; i < fs->size(); i++) // for each filament
    {
        glPushMatrix(); 
        glTranslatef(fs->at(i).x, fs->at(i).z, -fs->at(i).y);
        glPushAttrib(GL_LIGHTING_BIT);
        glCallList(SMOKE_MAT);
        glutSolidSphere(1.0, 8, 3);
        glPopAttrib();
        glPopMatrix();
    }
    glDisable(GL_BLEND);
}
/* End of draw_plume.cxx */
