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

/*--------------------------------------------------------------------------
 * draw the quad rotor
 *--------------------------------------------------------------------------
 */
/*--------------------------------------------------------------------------
 * draw the quad rotor rotor (main == 1: main rotor else tail rotor)
 *--------------------------------------------------------------------------
 */
static void draw_rotor(double outer_radius, double inner_radius)
{
  	double x1 = 0;
  	double x2 = 0;
  	double z1 = inner_radius;
  	double z2 = outer_radius;
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

static void draw_qr_model(qrstate_t qrstate, int shadow_arg)
{
	// double 	phi, roll_moment, pitch_moment;

	// phi = qrstate.phi;
	// roll_moment = qrstate.mx;
	// pitch_moment = qrstate.my;

  	shadow = shadow_arg;

    	glEnable(GL_LIGHTING); 
    	glEnable(GL_NORMALIZE);

  	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, 
		     shadow ? shadowed : grey);

	/* outer protective cover
	 */
  	glBegin(GL_LINES);

  	glVertex3f(1.0, 0.0, 0.5);
  	glVertex3f(1.0, 0.0, -0.5);

  	glVertex3f(1.0, 0.0, -0.5);
  	glVertex3f(0.5, 0.0, -1.0);

  	glVertex3f(0.5, 0.0, -1.0);
  	glVertex3f(-0.5, 0.0, -1.0);

  	glVertex3f(-0.5, 0.0, -1.0);
  	glVertex3f(-1.0, 0.0, -0.5);

  	glVertex3f(-1.0, 0.0, -0.5);
  	glVertex3f(-1.0, 0.0, 0.5);

  	glVertex3f(-1.0, 0.0, 0.5);
  	glVertex3f(-0.5, 0.0, 1.0);

  	glVertex3f(-0.5, 0.0, 1.0);
  	glVertex3f(0.5, 0.0, 1.0);

  	glVertex3f(0.5, 0.0, 1.0);
  	glVertex3f(1.0, 0.0, 0.5);
  	glEnd();

	/* motor struts
	 */
  	glBegin(GL_LINES);
  	glVertex3f(-0.55, 0.0, 0.0);
  	glVertex3f(0.55, 0.0, 0.0);

  	glVertex3f(0.0, 0.0, -0.55);
  	glVertex3f(0.0, 0.0, 0.55);
  	glEnd();

	/* 4 motors, 1st one ("led") blinks to indicate front of vehicle
	 */
	if (qrstate.leds && 0x0001) {
  		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, 
		     	shadow ? shadowed : red);
	}
  	glPushMatrix();
  	glTranslatef(0.55, 0.0, 0.0);
  	draw_rotor(0.08, 0.0);
  	glPopMatrix();

	/* solid color on the bottom
	 */
  	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, 
		     shadow ? shadowed : yellow);
  	glPushMatrix();
  	glTranslatef(0.55, -0.01, 0.0);
  	draw_rotor(0.08, 0.0);
  	glPopMatrix();

  	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, 
		     shadow ? shadowed : grey);

	/* other 3 motors
	 */
  	glPushMatrix();
  	glTranslatef(0.0, 0.0, 0.55);
  	draw_rotor(0.08, 0.0);
  	glPopMatrix();

  	glPushMatrix();
  	glTranslatef(-0.55, 0.0, 0.0);
  	draw_rotor(0.08, 0.0);
  	glPopMatrix();

  	glPushMatrix();
  	glTranslatef(0.0, 0.0, -0.55);
  	draw_rotor(0.08, 0.0);
  	glPopMatrix();


	/* 4 rotor covers
	 */
  	glPushMatrix();
  	glTranslatef(0.55, 0.0, 0.0);
  	draw_rotor(0.35, 0.33);
  	glPopMatrix();

  	glPushMatrix();
  	glTranslatef(0.0, 0.0, 0.55);
  	draw_rotor(0.35, 0.33);
  	glPopMatrix();

  	glPushMatrix();
  	glTranslatef(-0.55, 0.0, 0.0);
  	draw_rotor(0.35, 0.33);
  	glPopMatrix();

  	glPushMatrix();
  	glTranslatef(0.0, 0.0, -0.55);
  	draw_rotor(0.35, 0.33);
  	glPopMatrix();

  	glEnable(GL_LIGHTING);
}

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
