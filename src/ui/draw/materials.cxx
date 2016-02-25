/*
 * Materials for drawing using OpenGL
 *
 * This file contains the lists creation of materials.
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-24 create this file
 */

#include <FL/gl.h>
#include "materials.h"

/* material attribs */
GLfloat land_ambuse[] =   { 0.4, 0.2, 0.0, 0.2 };
GLfloat land_specular[] = { 0.394, 0.272, 0.167, 1.0 };
GLfloat land_shininess[] = { 0 };
    
GLfloat shadow_ambuse[] =   { 0, 0, 0, 0.2 };
GLfloat shadow_specular[] = { 0, 0, 0, 1.0 };
GLfloat shadow_shininess[] = { 0 };
    
GLfloat steel_ambuse[] =   { 0.05, 0.05, 0.05, 1.0 };
GLfloat steel_specular[] = { 0, 0, 0, 1.0 };
GLfloat steel_shininess[] = { 0 };

GLfloat cement_ambuse[] =   { 0.54, 0.54, 0.54, 0.2 };
GLfloat cement_specular[] = { 0, 0, 0, 1.0 };
GLfloat cement_shininess[] = { 0 };

GLfloat grass_ambuse[] =   { 0.0, 0.54, 0.0, 0.1 };
GLfloat grass_specular[] = { 0, 0, 0, 1.0 };
GLfloat grass_shininess[] = { 0 };

/* functions to create different materials */
static void create_land_material(void)
{
    glNewList(LAND_MAT, GL_COMPILE);
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, land_ambuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, land_specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, land_shininess);
    glEndList();
}

static void create_shadow_material(void)
{
    glNewList(SHADOW_MAT, GL_COMPILE);
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, shadow_ambuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, shadow_specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, shadow_shininess);
    glEndList();
}

static void create_steel_material(void)
{
    glNewList(STEEL_MAT, GL_COMPILE);
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, steel_ambuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, steel_specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, steel_shininess);
    glEndList();
}

static void create_cement_material(void)
{
    glNewList(CEMENT_MAT, GL_COMPILE);
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cement_ambuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, cement_specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, cement_shininess);
    glEndList();
}

static void create_grass_material(void)
{
    glNewList(GRASS_MAT, GL_COMPILE);
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, grass_ambuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, grass_specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, grass_shininess);
    glEndList();
}

void create_materials(void)
{
    create_land_material();
    create_steel_material();
    create_shadow_material();
    create_cement_material();
    create_grass_material();
}

/* End of materials.cxx */