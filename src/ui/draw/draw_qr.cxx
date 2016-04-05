/*
 * 3D QuadRotor Drawing
 *          using OpenGL GLUT
 *
 * This file contains stuff for drawing a quadrotor for 3D
 * Robot Active Olfaction using OpenGL GLUT.
 * The declarations of the classes or functions are written in 
 * file draw_qr.h, which is included by DrawScene.h
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-23 create this file
 */

#include <stdio.h>

#include <math.h>
#include <FL/gl.h>
#include "ui/draw/materials.h" // use material lists
#include "model/robot.h"
#include "model/quadrotor.h"

#ifndef PI
#define PI 3.14159265
#endif /*  */

/* graphics stuff */
static double RAD2DEG = 180 / PI;

/* declarations of local functions */
// simple planar
static void draw_motor(double);
static void draw_rotor(double);
static void draw_qr_model(RobotState_t*, QRframe_t*, int shadow);
static void draw_qr_mast(float);

/* draw the quad rotor, simple planar */
void draw_qr(RobotState_t* state, QRframe_t* frame)
{
    double phi, theta, psi;
	double glX, glY, glZ;
    float mat[] = {
    		1.0, 0.0, 0.0, 0.0,
    		0.0, 0.0, 0.0, 0.0,
    		0.0, 0.0, 1.0, 0.0,
    		0.0, 0.0, 0.0, 1.0
  	};
    /* change from NASA airplane to OpenGL coordinates */
  	glX = state->pos[0];
	glZ = -state->pos[1];
	glY = state->pos[2];
 	phi = state->attitude[0];
	theta = state->attitude[1];
	psi = state->attitude[2];

    /* draw the quad rotor */
    glPushMatrix(); 
    /* translate to pos of quadrotor */
    glTranslatef(glX, glY, glZ);
    /* apply NASA aeroplane Euler angles standard
	 * (in terms of OpenGL X,Y,Z frame where
	 * Euler earth axes X,Y,Z are openGl axes X,Z,-Y)
	 */
  	glRotatef(RAD2DEG * psi, 0.0, -1.0, 0.0);
  	glRotatef(RAD2DEG * theta, 0.0, 0.0, 1.0);
  	glRotatef(RAD2DEG * phi, 1.0, 0.0, 0.0);
    /* draw the mast of quad rotor, indicating up/down */
    draw_qr_mast(frame->size);

  	draw_qr_model(state, frame, 0);
      	
  	glPopMatrix();

#if 1
    /* draw the on-the-ground shadow of quad rotor */	
    glPushMatrix();
    glTranslatef(glX, 0.0, glZ);	
    glMultMatrixf(mat);
  	
    /* apply NASA aeroplane Euler angles standard
	 * (same drill) */
    glRotatef(RAD2DEG * psi, 0.0, -1.0, 0.0);
  	glRotatef(RAD2DEG * theta, 0.0, 0.0, 1.0);
  	glRotatef(RAD2DEG * phi, 1.0, 0.0, 0.0);

  	glEnable(GL_BLEND);
  	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  	draw_qr_model(state, frame, 1); 

  	glDisable(GL_BLEND);
  	glPopMatrix();
#endif
}

// basic for draw_motor and draw_rotor
static void draw_ring(double inner_radius, double outer_radius)
{
  	double x1 = 0;
  	double x2 = 0;
  	double z1 = inner_radius;;
  	double z2 = outer_radius;;
  	double k;
  	double newx1, newz1, newx2, newz2;
     
  	for (k = 0; k <= 2 * PI; k += PI / 12) {
      		newx1 = outer_radius * sin(k);
      		newz1 = outer_radius * cos(k);
      		newx2 = inner_radius * sin(k);
      		newz2 = inner_radius * cos(k);
      		glBegin(GL_POLYGON);
      		glVertex3f(x2, 0.0, z2);
      		glVertex3f(x1, 0.0, z1);
      		glVertex3f(newx1, 0.0, newz1);
      		glVertex3f(newx2, 0.0, newz2);
      		glEnd();
      		x1 = newx1;
      		x2 = newx2;
      		z1 = newz1;
      		z2 = newz2;
    	}
}

/* local functions 
 * draw motors, propellers ... */
static void draw_motor(double size)
{
    draw_ring(0, size);
}

/* draw the quad rotor rotor (main == 1: main rotor else tail rotor) */
static void draw_rotor(double radius)
{
    draw_ring(radius*1.03, radius*0.97);
}

static void draw_qr_model(RobotState_t* state, QRframe_t* frame, int shadow)
{
    GLfloat qr_strut_r; // frame_size/2
    GLfloat qr_prop_r; // propeller radius
    GLfloat qr_cover_s; // cover size
    GLfloat qr_cover_s_x; // cover size * 2
    GLfloat qr_motor_s; // motor size (radius)

    qr_strut_r = frame->size/2.0;
    qr_prop_r = frame->prop_radius;

    glPushAttrib(GL_LIGHTING_BIT);

   /* motor struts */
    glCallList(shadow?SHADOW_MAT:STEEL_MAT);
  	glBegin(GL_LINES);
  	glVertex3f(-qr_strut_r, 0.0, 0.0);
  	glVertex3f(qr_strut_r, 0.0, 0.0);

  	glVertex3f(0.0, 0.0, -qr_strut_r);
  	glVertex3f(0.0, 0.0, qr_strut_r);
  	glEnd();

	/*  motors */
    qr_motor_s = qr_prop_r*0.24;// calculate motor size
    glPushMatrix();
  	glTranslatef(qr_strut_r, 0.0, 0.0);
  	draw_motor(qr_motor_s);
  	glPopMatrix();

  	glPushMatrix();
  	glTranslatef(0.0, 0.0, qr_strut_r);
  	draw_motor(qr_motor_s);
  	glPopMatrix();

  	glPushMatrix();
  	glTranslatef(-qr_strut_r, 0.0, 0.0);
  	draw_motor(qr_motor_s);
  	glPopMatrix();

  	glPushMatrix();
  	glTranslatef(0.0, 0.0, -qr_strut_r);
  	draw_motor(qr_motor_s);
  	glPopMatrix();

	/* 4 rotor covers (propeller tip locus)*/
  	glPushMatrix();
  	glTranslatef(qr_strut_r, 0.0, 0.0);
  	draw_rotor(qr_prop_r);
  	glPopMatrix();

  	glPushMatrix();
  	glTranslatef(0.0, 0.0, qr_strut_r);
  	draw_rotor(qr_prop_r);
  	glPopMatrix();

  	glPushMatrix();
  	glTranslatef(-qr_strut_r, 0.0, 0.0);
  	draw_rotor(qr_prop_r);
  	glPopMatrix();

  	glPushMatrix();
  	glTranslatef(0.0, 0.0, -qr_strut_r);
  	draw_rotor(qr_prop_r);
  	glPopMatrix();

#if 1
	/* outer protective cover */
    qr_cover_s = qr_strut_r*0.9; // decoration, can be turned off
    qr_cover_s_x = qr_cover_s*2;

    glCallList(shadow?SHADOW_MAT:STEEL_MAT);

  	glBegin(GL_LINES);

  	glVertex3f(qr_cover_s_x, 0.0, qr_cover_s);
  	glVertex3f(qr_cover_s_x, 0.0, -qr_cover_s);

  	glVertex3f(qr_cover_s_x, 0.0, -qr_cover_s);
  	glVertex3f(qr_cover_s, 0.0, -qr_cover_s_x);

  	glVertex3f(qr_cover_s, 0.0, -qr_cover_s_x);
  	glVertex3f(-qr_cover_s, 0.0, -qr_cover_s_x);

  	glVertex3f(-qr_cover_s, 0.0, -qr_cover_s_x);
  	glVertex3f(-qr_cover_s_x, 0.0, -qr_cover_s);

  	glVertex3f(-qr_cover_s_x, 0.0, -qr_cover_s);
  	glVertex3f(-qr_cover_s_x, 0.0, qr_cover_s);

  	glVertex3f(-qr_cover_s_x, 0.0, qr_cover_s);
  	glVertex3f(-qr_cover_s, 0.0, qr_cover_s_x);

  	glVertex3f(-qr_cover_s, 0.0, qr_cover_s_x);
  	glVertex3f(qr_cover_s, 0.0, qr_cover_s_x);

  	glVertex3f(qr_cover_s, 0.0, qr_cover_s_x);
  	glVertex3f(qr_cover_s_x, 0.0, qr_cover_s);

  	glEnd();
#endif

    /* "led" blinks, actually one propeller blinks */    
	if (state->leds && 0x0001 && !shadow) 
    {// turn on led (actually one motor)
        glDisable(GL_LIGHTING);
        glColor3f(1.0, 0.0, 0.0); /* red */
        glPushMatrix();
        {
            glTranslatef(qr_strut_r, 0.0, 0.0);
            draw_ring(qr_motor_s, qr_prop_r);
        }glPopMatrix();
        glEnable(GL_LIGHTING);
	}
  	
    glPopAttrib();
}

static void draw_qr_mast(float qrsize)
{
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 0.0, 0.0); /* red */
  	glBegin(GL_LINES);
  	glVertex3f(0.0, 0.0, 0.0);
  	glVertex3f(0.0, qrsize/2, 0.0);
  	glEnd();
    glEnable(GL_LIGHTING);
}

/* End of draw_qr.cxx */
