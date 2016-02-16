/*
 * 3D View of Robot Active Olfaction
 *          using OpenGL
 *
 * This file defines the classes of the scene drawing for 3D
 * Robot Active Olfaction using OpenGL lib.
 * This file is included by SimUi.cxx, and the classes are
 * integrated into the FLTK UI.
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-16 create this file
 */

#ifndef SIMVIEW_H
#define SIMVIEW_H

#include <stdio.h>
#include <math.h>

// OpenGL spinning cube with checker texturemap -- erco/loic 03/17/09
//
#define WIN_W 400       // window width
#define WIN_H 400       // window height
#define TEX_W 64        // texturemap width
#define TEX_H 64        // texturemap height
#define FPS (1.0/24.0)  // frames per second playback
//
// OpenGL class to show texturemapped cube
//
class MyGlWindow : public Fl_Gl_Window {
    double spin;
    GLuint TexID;
    // TIMER CALLBACK
    //    Handles rotation the object
    //
    static void Timer_CB(void *userdata) {
        MyGlWindow *mygl = (MyGlWindow*)userdata;
        mygl->spin += 2.0;       // spin
        mygl->redraw();
        Fl::repeat_timeout(FPS, Timer_CB, userdata);
    }
public:
    // CTOR
    MyGlWindow(int x,int y,int w,int h,const char *l=0) : Fl_Gl_Window(x,y,w,h,l) {
        spin = 0.0;
        Fl::add_timeout(FPS, Timer_CB, (void*)this);       // 24fps timer
    }
    // PERSPECTIVE VIEW
    //    Same as gluPerspective()..
    //
    void Perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
        GLdouble xmin, xmax, ymin, ymax;
        ymax = zNear * tan(fovy * M_PI / 360.0);
        ymin = -ymax;
        xmin = ymin * aspect;
        xmax = ymax * aspect;
        glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
    }
    // RESHAPED VIEWPORT
    //     OpenGL stuff to do whenever window changes size
    //
    void ReshapeViewport() {
        // Viewport
        glViewport(0, 0, w(), h());
        // Projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        GLfloat ratio = w() / h();
        Perspective(30.0, 1.0*ratio, 1.0, 30.0);
        glTranslatef(0.0, 0.0, -8.0);
        // Model view
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    // OPENGL INITIALIZATION
    //    OpenGL stuff to do *only once* on startup.
    //
    void GlInit() {
        // Make sure we only do this once
        static int first_time = 1;
        if ( first_time ) {
            first_time = 0;
            // Texture Map Init
            GLubyte img[TEX_W][TEX_H][3]; // after glTexImage2D(), array is no longer needed
            glGenTextures(1, &TexID);
            glBindTexture(GL_TEXTURE_2D, TexID);
      
            /*** Texture Mapping Mode
             ***    Uncomment one of the following lines: GL_DECAL or GL_MODULATE
             ***/
            //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);   // use actual texture colors
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // texture colors affected by poly's color
      
            for (int x=0; x<TEX_W; x++) {
                for (int y=0; y<TEX_H; y++) {

                    /*** Texture Pattern
                     ***     Uncomment one of the following lines: checkboard or basketweave
                     ***/
                    //GLubyte c = ((x&16)^(y&16)) ? ((x%16)<<4) : (((x%16)^15)<<4); // basket weave
                    GLubyte c = ((x&16)^(y&16)) ? 255 : 0;                          // checkerboard

                    img[x][y][0] = c;
                    img[x][y][1] = c;
                    img[x][y][2] = c;
                }
            }
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEX_W, TEX_H, 0, GL_RGB, GL_UNSIGNED_BYTE, &img[0][0][0]);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glEnable(GL_TEXTURE_2D);
            // Misc OpenGL settings
            glShadeModel(GL_FLAT);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
        }
    }
    // FLTK DRAW
    //    Called by FLTK to draw the scene.
    //
    void draw() {
        // Initialize/handle reshaped viewport
        if ( !valid() ) {
            valid(1);
            GlInit();
            ReshapeViewport();
        }
        // Clear
        glClearColor(.5,.5,.5, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Setup model matrix
        glLoadIdentity();
        glRotatef(spin, 0.5, 1.0, 0.0); // show all sides of cube
        // Draw cube with texture assigned to each face
        glBegin(GL_QUADS);
          // Front Face
          glColor3f(1.0, 0.0, 0.0); // red
              glTexCoord2f(0.0, 1.0); glVertex3f(-1.0,  1.0,  1.0); // Top Left Of The Texture and Quad
              glTexCoord2f(1.0, 1.0); glVertex3f( 1.0,  1.0,  1.0); // Top Right Of The Texture and Quad
              glTexCoord2f(1.0, 0.0); glVertex3f( 1.0, -1.0,  1.0); // Bottom Right Of The Texture and Quad
              glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0,  1.0); // Bottom Left Of The Texture and Quad
          // Back Face
          glColor3f(0.0, 1.0, 1.0); // cyn
              glTexCoord2f(0.0, 1.0); glVertex3f( 1.0,  1.0, -1.0); // Top Left Of The Texture and Quad
              glTexCoord2f(1.0, 1.0); glVertex3f(-1.0,  1.0, -1.0); // Top Right Of The Texture and Quad
              glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0, -1.0); // Bottom Right Of The Texture and Quad
              glTexCoord2f(0.0, 0.0); glVertex3f( 1.0, -1.0, -1.0); // Bottom Left Of The Texture and Quad
          // Top Face
          glColor3f(0.0, 1.0, 0.0); // grn
              glTexCoord2f(0.0, 1.0); glVertex3f(-1.0,  1.0, -1.0); // Top Left Of The Texture and Quad
              glTexCoord2f(1.0, 1.0); glVertex3f( 1.0,  1.0, -1.0); // Top Right Of The Texture and Quad
              glTexCoord2f(1.0, 0.0); glVertex3f( 1.0,  1.0,  1.0); // Bottom Right Of The Texture and Quad
              glTexCoord2f(0.0, 0.0); glVertex3f(-1.0,  1.0,  1.0); // Bottom Left Of The Texture and Quad
          // Bottom Face
          glColor3f(1.0, 0.0, 1.0); // mag
              glTexCoord2f(0.0, 1.0); glVertex3f( 1.0, -1.0, -1.0); // Top Left Of The Texture and Quad
              glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, -1.0, -1.0); // Top Right Of The Texture and Quad
              glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0,  1.0); // Bottom Right Of The Texture and Quad
              glTexCoord2f(0.0, 0.0); glVertex3f( 1.0, -1.0,  1.0); // Bottom Left Of The Texture and Quad
          // Right face
          glColor3f(0.0, 0.0, 1.0); // blu
              glTexCoord2f(0.0, 1.0); glVertex3f( 1.0,  1.0,  1.0); // Top Left Of The Texture and Quad
              glTexCoord2f(1.0, 1.0); glVertex3f( 1.0,  1.0, -1.0); // Top Right Of The Texture and Quad
              glTexCoord2f(1.0, 0.0); glVertex3f( 1.0, -1.0, -1.0); // Bottom Right Of The Texture and Quad
              glTexCoord2f(0.0, 0.0); glVertex3f( 1.0, -1.0,  1.0); // Bottom Left Of The Texture and Quad
          // Left Face
          glColor3f(1.0, 1.0, 0.0); // yel
              glTexCoord2f(0.0, 1.0); glVertex3f(-1.0,  1.0, -1.0); // Top Left Of The Texture and Quad
              glTexCoord2f(1.0, 1.0); glVertex3f(-1.0,  1.0,  1.0); // Top Right Of The Texture and Quad
              glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0,  1.0); // Bottom Right Of The Texture and Quad
              glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, -1.0); // Bottom Left Of The Texture and Quad
        glEnd();
        // DEBUG: CHECK FOR ERRORS
        GLenum err = glGetError();
        if ( err != GL_NO_ERROR ) {
            fprintf(stderr, "GLGETERROR=%d\n", (int)err);
        }
    }
};

#endif
