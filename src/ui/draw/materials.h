/*
 * Materials for drawing using OpenGL
 *
 * This file defines DisplayLists enum. The lists creation are written in
 * material.cxx
 * This file is included by draw_qr.cxx draw_arena.cxx ... to set materials
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-24 create this file
 */

typedef enum {LAND_MAT, STEEL_MAT, CEMENT_MAT, GRASS_MAT, SMOKE_MAT, SHADOW_MAT, VORTICE_MAT, CHLORINE_MAT} DisplayLists;

void create_materials(void);
void SimMaterial_smoke(float);
void SimMaterial_chlorine(float);
/* End of materials.h */
