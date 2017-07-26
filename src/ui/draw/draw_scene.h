/*
 * 3D RAO Sim Scene Drawing
 *          using OpenGL GLUT
 *
 * This file defines stuff for drawing the simulation scene for 3D
 * Robot Active Olfaction using OpenGL GLUT.
 * This file is included by RAOS_view.cxx, and the implementations are
 * written in draw_scene.cxx, which contains functions of files 
 * draw_qr.cxx, draw_pl.cxx, draw_wind.cxx
 *
 * draw_qr.cxx  OpenGL drawing of a quadrotor
 * draw_pl.cxx  OpenGL drawing of plume filaments (Farrell's model)
 * draw_wind.cxx OpenGL drawing of wind vectors
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-23 create this file
 *       2017-07-21 rename this file from DrawScene.h to draw_scene.h
 */

#ifndef DRAW_SCENE_H
#define DRAW_SCENE_H

void draw_scene_init();
void draw_scene_update();

#endif
/* End of draw_scene.h */
