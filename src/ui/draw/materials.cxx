/*
 * Materials for drawing using OpenGL
 *
 * This file contains the lists creation of materials.
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-24 create this file
 */

#include <FL/gl.h>
#include "ui/draw/materials.h"

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

GLfloat smoke_ambuse[] =   { 0.0, 0.0, 0.0, 0.3 };
GLfloat smoke_specular[] = { 0, 0, 0, 1.0 };
GLfloat smoke_shininess[] = { 0 };

GLfloat vortice_ambuse[] =   { 0.6, 0.6, 0.6, 0.3 };
GLfloat vortice_specular[] = { 0, 0, 0, 1.0 };
GLfloat vortice_shininess[] = { 0 };

GLfloat chlorine_ambuse[] =   { 0.0, 1.0, 0.0, 0.3 };
GLfloat chlorine_specular[] = { 0, 0, 0, 1.0 };
GLfloat chlorine_shininess[] = { 0 };

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

static void create_smoke_material(void)
{
    glNewList(SMOKE_MAT, GL_COMPILE);
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, smoke_ambuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, smoke_specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, smoke_shininess);
    glEndList();
}

static void create_vortice_material(void)
{
    glNewList(VORTICE_MAT, GL_COMPILE);
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, vortice_ambuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, vortice_specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, vortice_shininess);
    glEndList();
}

static void create_chlorine_material(void)
{
    glNewList(CHLORINE_MAT, GL_COMPILE);
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, chlorine_ambuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, chlorine_specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, chlorine_shininess);
    glEndList();
}

void create_materials(void)
{
    create_land_material();
    create_steel_material();
    create_shadow_material();
    create_cement_material();
    create_grass_material();
    create_smoke_material();
    create_vortice_material();
    create_chlorine_material();
}

// changeable smoke material
void SimMaterial_smoke(float c)
{// 0.0 <= c <= 1.0
    if (c <= 0.)
        smoke_ambuse[3] = 0.01;
    else if (c >= 1.)
        smoke_ambuse[3] = 1.0;
    else
        smoke_ambuse[3] = c;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, smoke_ambuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, smoke_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, smoke_shininess);
}

// changeable chlorine material
void SimMaterial_chlorine(float c)
{// 0.0 <= c <= 1.0
    if (c <= 0.)
        chlorine_ambuse[3] = 0.01;
    else if (c >= 1.)
        chlorine_ambuse[3] = 1.0;
    else
        chlorine_ambuse[3] = c;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, chlorine_ambuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, chlorine_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, chlorine_shininess);
}

/* End of materials.cxx */
