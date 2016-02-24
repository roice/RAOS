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
#include "qrmod.h"


#ifndef PI
#define PI 3.14159265
#endif /*  */

/* graphics stuff */
static double RAD2DEG = 180 / PI;

GLfloat red[4] = { 0.4, 0.0, 0.0, 1.0 };
GLfloat yellow[4] = { 0.9, 0.9, 0.0, 1.0 };
GLfloat grey[4] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat shadowed[4] = { 0.0, 0.0, 0.0, 0.2 };

int 	shadow = 0;

/* declarations of local functions */
// simple planar
static void draw_motor(double);
static void draw_rotor(double);
static void draw_qr_model(qrstate_t, int);
static void draw_qr_mast(float);
// normal 3d
static void draw_motor_3d(double);
static void draw_rotor_3d(double);
static void draw_qr_model_3d(qrstate_t, int);

/* draw the quad rotor, simple planar */
void draw_qr(qrstate_t qrstate)
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
  	glX = qrstate.x;
	glZ = qrstate.y;
	glY = -qrstate.z;
 	phi = qrstate.phi;
	theta = qrstate.theta;
	psi = qrstate.psi;

    /* draw the mast of quad rotor, indicating up/down */
    draw_qr_mast(qrstate.frame.size);

    /* draw the quad rotor */
  	glEnable(GL_LIGHTING);
  	glPushMatrix();
  	glTranslatef(glX, glY, glZ);

	/* apply NASA aeroplane Euler angles standard
	 * (in terms of OpenGL X,Y,Z frame where
	 * Euler earth axes X,Y,Z are openGl axes X,Z,-Y)
	 */
  	glRotatef(RAD2DEG * psi, 0.0, -1.0, 0.0);
  	glRotatef(RAD2DEG * theta, 0.0, 0.0, 1.0);
  	glRotatef(RAD2DEG * phi, 1.0, 0.0, 0.0);

  	draw_qr_model(qrstate, 0);

  	glPopMatrix();
  	glPushMatrix();
  	glTranslatef(glX, 0.0, glZ);
  	glMultMatrixf(mat);

    /* draw the on-the-ground shadow of quad rotor */
	/* apply NASA aeroplane Euler angles standard
	 * (same drill)
	 */
  	glRotatef(RAD2DEG * psi, 0.0, -1.0, 0.0);
  	glRotatef(RAD2DEG * theta, 0.0, 0.0, 1.0);
  	glRotatef(RAD2DEG * phi, 1.0, 0.0, 0.0);

  	glEnable(GL_BLEND);
  	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  	draw_qr_model(qrstate, 1); 

  	glDisable(GL_BLEND);
  	glPopMatrix();
}

/* draw the quad rotor, normal 3d */
void draw_qr_3d(qrstate_t qrstate)
{}

/* local functions 
 * draw motors, propellers ... */
static void draw_motor(double size)
{
  	double x1 = 0;
  	double x2 = 0;
  	double z1;
  	double z2;
  	double k;
  	double newx1, newz1, newx2, newz2;

    double outer_radius = size; // for beauty
    double inner_radius = 0;
    z1 = inner_radius;
    z2 = outer_radius;
     
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

/* draw the quad rotor rotor (main == 1: main rotor else tail rotor) */
static void draw_rotor(double radius)
{
  	double x1 = 0;
  	double x2 = 0;
  	double z1;
  	double z2;
  	double k;
  	double newx1, newz1, newx2, newz2;

    double outer_radius = radius*1.03; // for beauty
    double inner_radius = radius*0.97;
    z1 = inner_radius;
    z2 = outer_radius;
     
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

static void draw_qr_model(qrstate_t qrstate, int shadow_arg)
{
    GLfloat qr_strut_r; // frame_size/2
    GLfloat qr_prop_r; // propeller radius
    GLfloat qr_cover_s; // cover size
    GLfloat qr_cover_s_x; // cover size * 2
    GLfloat qr_motor_s; // motor size (radius)

    qr_strut_r = qrstate.frame.size/2;
    qr_prop_r = qrstate.frame.prop_radius;

  	shadow = shadow_arg;
    glEnable(GL_LIGHTING); 
    glEnable(GL_NORMALIZE);
  	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, 
		     shadow ? shadowed : grey);

#if 1
	/* outer protective cover */
    qr_cover_s = qr_strut_r*0.9; // decoration, can be turned off
    qr_cover_s_x = qr_cover_s*2;

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

   /* motor struts */
  	glBegin(GL_LINES);
  	glVertex3f(-qr_strut_r, 0.0, 0.0);
  	glVertex3f(qr_strut_r, 0.0, 0.0);

  	glVertex3f(0.0, 0.0, -qr_strut_r);
  	glVertex3f(0.0, 0.0, qr_strut_r);
  	glEnd();

	/* 4 motors, 1st one ("led") blinks to indicate front of vehicle
	 */
    qr_motor_s = qr_prop_r*0.24;// calculate motor size
	if (qrstate.leds && 0x0001) {
  		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, 
		     	shadow ? shadowed : red);
	}
  	glPushMatrix();
  	glTranslatef(qr_strut_r, 0.0, 0.0);
  	draw_motor(qr_motor_s);
  	glPopMatrix();

	/* solid color on the bottom
	 */
  	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, 
		     shadow ? shadowed : yellow);
  	glPushMatrix();
  	glTranslatef(qr_strut_r, -0.01, 0.0);
  	draw_motor(qr_motor_s);
  	glPopMatrix();

  	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, 
		     shadow ? shadowed : grey);

	/* other 3 motors
	 */
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

  	glEnable(GL_LIGHTING);
}

static void draw_qr_mast(float qrsize)
{
    glEnable(GL_NORMALIZE);
  	glDisable(GL_LIGHTING);
  	glColor3f(0.0, 0.0, 0.0); /* black */
  	glBegin(GL_LINES);
  	glVertex3f(0.0, 0.0, 0.0);
  	glVertex3f(0.0, qrsize/2, 0.0);
  	glEnd(); 
}
/* End of draw_qr.cxx */
