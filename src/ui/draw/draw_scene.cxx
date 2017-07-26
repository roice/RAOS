/*
 * 3D RAO Sim Scene Drawing
 *          using OpenGL GLUT
 *
 * This file implements stuff for drawing the simulation scene for 3D
 * Robot Active Olfaction using OpenGL GLUT.
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-23 create this file
 *       2017-07-21 rename this file from DrawScene.cxx to draw_scene.cxx
 */

#include GL_HEADER

/* thread */
#include <pthread.h>
/* RAOS */
#include "ui/draw/materials.h" // create material lists
#include "ui/draw/draw_arena.h" // arena visualization
//#include "ui/draw/draw_plume.h" // plume visual
//#include "ui/draw/draw_robots.h" // robots visualization
//#ifdef RAOS_FEATURE_WAKES
//    #include "ui/draw/draw_wake.h" // wake visual
//#endif
//#include "ui/draw/draw_ref_point.h"


GLfloat localAmb[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat ambient0[4] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat diffuse0[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat specular0[4] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat ambient1[4] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat diffuse1[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat specular1[4] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat position0[4] = { 2.0, 100.5, 1.5, 1.0 };
GLfloat position1[4] = { -2.0, 100.5, 1.0, 0.0 };

/*--------------------------------------------------------------------------
 * draw everything (environment + quad rotor)
 *--------------------------------------------------------------------------
 */
void draw_scene_update(void)
{ 
    /* GL stuff */
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, localAmb);
  	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
  	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
  	glEnable(GL_LIGHT0);
  	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
  	glLightfv(GL_LIGHT0, GL_POSITION, position0);
  	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
  	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
  	glEnable(GL_LIGHT1);
  	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
  	glLightfv(GL_LIGHT1, GL_POSITION, position1);
  	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
  	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  	glLoadIdentity();
    glEnable(GL_LIGHTING); // default enable for the rest routines

    /* draw arena */
    draw_arena(SIM_ARENA_BASIC);

    /* draw wind field */

    /* draw plumes */

    /* draw robots */

    /* draw wakes */

#if 0
    if (!sim_is_running_or_not())
        return;

    pthread_mutex_lock(sim_get_data_lock());

    /* draw quadrotor */
    draw_ref_point(SimModel_get_robots());
    draw_robots(SimModel_get_robots());

#ifdef RAOS_FEATURE_WAKES
    /* draw rotor wakes */
    draw_wake(SimModel_get_robots());
#endif

    /* draw plume */
    draw_plume();

    pthread_mutex_unlock(sim_get_data_lock());
#endif
}

void draw_scene_init(void) // call before draw_scene_update
{
    create_materials();
}
/* End of draw_scene.cxx */
