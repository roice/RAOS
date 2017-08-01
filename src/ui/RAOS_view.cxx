/*
 * 3D View of Robot Active Olfaction
 *          using OpenGL
 *
 * This file implements the classes of the view displaying for 3D
 * Robot Active Olfaction using OpenGL lib.
 * This file is included by RAOS_UI.cxx, and the classes are
 * integrated into the FLTK UI.
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-23 create this file
 */

/* functions of class RAOS_view which implements glut callbacks in RAOS_UI.cxx */

#include GLUT_HEADER
#include GLU_HEADER
#include <string.h>
#include <time.h> // for srand seeding and FPS calculation
#include "FL/gl_draw.H"
/* RAOS */
#include "RAOS_config.h"
#include "ui/agv.h" // eye movement
#include "ui/draw/draw_scene.h" // draw sim scene
#include "model/RAOS_model.h"

// width and height of current window, for redraw function
static int sim_width = 1;
static int sim_height = 1;

static void RAOS_view_reshape(int w, int h)
{
    // update width/height of window
    sim_width = w;
    sim_height = h;

    glViewport(0, 0, w, h);
}

static void draw_axes(void);// draw axes
static void draw_notes(void);//draw notes
static void RAOS_view_redraw(void)
{
    /* change eye moving */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, (GLdouble)sim_width/sim_height, 0.01, 1000);
    agvViewTransform();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* Begin drawing simulation scene */
    draw_scene_update(); // draw sim scene
    /* End drawing */

    /* draw axes on the ground */
    draw_axes();

    /* draw note */
    draw_notes();
    
    //glutSwapBuffers(); // using two buffers mode

    // Use glFinish() instead of glFlush() to avoid getting many frames
    // ahead of the display (problem with some Linux OpenGL implementations...)
    //glFinish(); 
}

static void RAOS_view_visible(int v)
{
    if (v == GLUT_VISIBLE)
        agvSetAllowIdle(1);
    else
    {
        glutIdleFunc(NULL);
        agvSetAllowIdle(0);
    }
}

static void draw_axes(void)
{
    float ORG[3] = {0,0,0};
    float XP[3] = {0,0,0}, YP[3] = {0,0,0};
    /* get configs about arena size */
    RAOS_config_t *config = RAOS_config_get_settings();
    XP[0] = config->arena.w?config->arena.w/2.0+1:5;
    YP[2] = config->arena.l?-(config->arena.l/2.0+1):-5;
    
    // draw x,y axes
    glDisable(GL_LIGHTING);
    {
        glLineWidth(2.0);
        glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3fv(ORG);
        glVertex3fv(XP);    // X axis is red.
        glColor3f(0,0,1);
        glVertex3fv(ORG);
        glVertex3fv(YP);    // y axis is blue.
        glEnd();

        // draw labels
        const char *str_x = "X/East";
        const char *str_y = "Y/North";
        glDisable(GL_DEPTH_TEST);
        glColor3f(0.3, 0.3, 0.3); // gray
        glRasterPos3fv(XP);
        gl_font(FL_HELVETICA_BOLD, 12); 
        gl_draw(str_x, strlen(str_x));
        glRasterPos3fv(YP); 
        gl_draw(str_y, strlen(str_y));
        glEnable(GL_DEPTH_TEST);
    }glEnable(GL_LIGHTING);
}

static void draw_ui_fps_note(void)
{
    time_t curtime; // current time
    char buf[255];
    static time_t fpstime = 0;
    static int fpscount = 0;
    static int fps = 0;

    glDisable(GL_LIGHTING);
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, sim_width, 0.0, sim_height);
        sprintf(buf, "FPS=%d", fps);
        glColor3f(1.0f, 1.0f, 1.0f);
        gl_font(FL_HELVETICA, 12);
        gl_draw(buf, 10, 10);
    }glEnable(GL_LIGHTING);

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

static void draw_sim_time_note(void)
{
    char buf[256];

    if (!RAOS_model_thread_is_running())
        return;

    double time_passed = (RAOS_model_thread_get_state())->time_passed;
    
    glDisable(GL_LIGHTING);
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, sim_width, 0.0, sim_height);
        sprintf(buf, "Time = %d m %.1f s", (int)(time_passed/60), time_passed-((int)(time_passed/60))*60);
        glColor3f(1.0f, 1.0f, 1.0f);
        gl_font(FL_HELVETICA, 12);
        gl_draw(buf, 200, 10);
    }glEnable(GL_LIGHTING);
}

static void draw_sim_speed_note(void)
{
    char buf[256];

    if (!RAOS_model_thread_is_running())
        return;

    double real_speed = (RAOS_model_thread_get_state())->speed;
    
    glDisable(GL_LIGHTING);
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, sim_width, 0.0, sim_height);
        sprintf(buf, "Real Speed = %.1f", real_speed);
        glColor3f(1.0f, 1.0f, 1.0f);
        gl_font(FL_HELVETICA, 12);
        gl_draw(buf, 400, 10);
    }glEnable(GL_LIGHTING);
}

static void draw_notes(void) {
    draw_ui_fps_note();     // frames per second of UI
    draw_sim_time_note(); // simulation time passed since start
    draw_sim_speed_note(); // simulation speed
}


static void RAOS_view_idle(int) {
    glutTimerFunc((unsigned int)(1000./60.), RAOS_view_idle, 0); // FPS 60
    // update view
    if (agvMoving) agvMove();
    RAOS_view_redraw();
    glutPostRedisplay();
}

void RAOS_view_init(int width, int height)
{
    // set width/height of window
    sim_width = width;
    sim_height = height;

    agvInit(0); /* 0 cause we have our own idle */
    // config callbacks for glut
    //  these functions will not be called immediately
    glutReshapeFunc(RAOS_view_reshape);
    glutDisplayFunc(RAOS_view_redraw);
    glutVisibilityFunc(RAOS_view_visible);
    glutTimerFunc((unsigned int)(1000./60.), RAOS_view_idle, 0); // FPS 60

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
    gluPerspective(30.0, (GLdouble)width/height, 0.01, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* init sim scene drawing */
    draw_scene_init();
}
/* End of RAOS_view.cxx */
