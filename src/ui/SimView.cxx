/*
 * 3D View of Robot Active Olfaction
 *          using OpenGL
 *
 * This file implements the classes of the view displaying for 3D
 * Robot Active Olfaction using OpenGL lib.
 * This file is included by SimUI.cxx, and the classes are
 * integrated into the FLTK UI.
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-23 create this file
 */

/* functions of class SimView which implements glut callbacks in SimUI.cxx */

#include <FL/glut.H>
#include <FL/glu.h>
#include <time.h> // for srand seeding and FPS calculation
#include "agv.h" // eye movement
#include "draw/DrawScene.h" // draw sim scene

typedef enum { AXES } DisplayLists;

// width and height of current window, for display function
int win_width = 1;
int win_height = 1;

void SimView_init(int width, int height)
{
    // update width/height of window
    win_width = width;
    win_height = height;

    agvInit(1); /* 1 cause we don't have our own idle */

    agvMakeAxesList(AXES);

    /* Initialize GL stuff */
    glShadeModel(GL_FLAT);// or use GL_SMOOTH with more computation
    glClearColor(0.49, 0.62, 0.75, 0.0);
  	glClearDepth(1.0f);
  	glEnable(GL_DEPTH_TEST);// can disable for lower computation
  	glDepthFunc(GL_LEQUAL);
  	glDisable(GL_BLEND);// cause GL_DEPTH_TEST enabled
  	glDisable(GL_ALPHA_TEST);
  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
    gluPerspective(60.0, (GLdouble)win_width/win_height, 0.01, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SimView_reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

void SimView_redraw(void)
{
    time_t curtime; // current time
    char buf[255];
    static time_t fpstime = 0;
    static int fpscount = 0;
    static int fps = 0;
  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color buffer and depth buffer
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLdouble)win_width/win_height, 0.01, 100);
    agvViewTransform();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* Begin drawing simulation scene */
    DrawScene(); // draw sim scene

    /* End drawing */

    if (true) glCallList(AXES);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, win_width, 0.0, win_height);

    sprintf(buf, "FPS=%d", fps);
    glColor3f(1.0f, 1.0f, 1.0f);
    gl_font(FL_HELVETICA, 12);
    gl_draw(buf, 10, 10);

  // Use glFinish() instead of glFlush() to avoid getting many frames
  // ahead of the display (problem with some Linux OpenGL implementations...)
    glFinish();

    // Update frames-per-second
    fpscount ++;
    curtime = time(NULL);
    if ((curtime - fpstime) >= 2)
    {
        fps      = (fps + fpscount / (curtime - fpstime)) / 2;
        fpstime  = curtime;
        fpscount = 0;
    }
}

void SimView_visible(int v)
{
    if (v == GLUT_VISIBLE)
        agvSetAllowIdle(1);
    else
    {
        glutIdleFunc(NULL);
        agvSetAllowIdle(0);
    }
}
