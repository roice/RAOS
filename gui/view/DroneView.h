//
// DroneView class definitions for the FGCS_3DAO(FLTK Ground Control 
// Station for Three Dimension Active Olfaction).
// 
// Author: Roice (Bing LUO)
// Date: 2014-11-18 create this file
//

#ifndef DRONEVIEW_H
#define DRONEVIEW_H 1
#include <config.h>
#include <FL/Fl.H>
#if HAVE_GL
#  include <FL/Fl_Gl_Window.H>
#  include <FL/gl.h>
#else
#  include <FL/Fl_Box.H>
#endif /* HAVE_GL */

#include <stdlib.h>

#if HAVE_GL
class DroneView : public Fl_Gl_Window {
#else
class DroneView : public Fl_Box {
#endif /* HAVE_GL */

public:
    // this value determines the scaling factor used to draw the drone.
    double size;

    DroneView(int x,int y,int w,int h,const char *l=0);

    /* Set the rotation about the vertical (y ) axis.
     *
     * This function is called by the horizontal roller in DroneViewUI and the
     * initialize button in DroneViewUI.
     */
    void v_angle(double angle){vAng=angle;}
    
    // Return the rotation about the vertical (y ) axis.
    double v_angle() const {return vAng;}

    /* Set the rotation about the horizontal (x ) axis.
     *
     * This function is called by the vertical roller in DroneViewUI and the
     * initialize button in DroneViewUI.
     */

    void h_angle(double angle){hAng=angle;}

    // the rotation about the horizontal (x ) axis.
    double h_angle() const {return hAng;}

    /* Sets the x shift of the drone view camera.
     *
     * This function is called by the slider in DroneViewUI and the
     * initialize button in DroneViewUI.
     */
    void panx(double x){xshift=x;}
    /* Sets the y shift of the drone view camera.
     *
     * This function is called by the slider in DroneViewUI and the
     * initialize button in DroneViewUI.
     */
    void pany(double y){yshift=y;}

#if HAVE_GL
    /*The widget class draw() override.
     *
     *The draw() function initialize Gl for another round o f drawing
     * then calls specialized functions for drawing each of the
     * entities displayed in the drone view.
     *
     */
    void draw();    
#endif /* HAVE_GL */
private:

    /*  Draw the drone boundaries
     *
     *Draw the faces of the drone using the boxv[] vertices, using
     * GL_LINE_LOOP for the faces. The color is \#defined by DRONECOLOR.
     */
#if HAVE_GL
    void drawDrone();
#else
    void drawDrone() { }
#endif /* HAVE_GL */
    
    double vAng,hAng;
    double xshift,yshift;


    float boxv0[3];float boxv1[3];
    float boxv2[3];float boxv3[3];
    float boxv4[3];float boxv5[3];
    float boxv6[3];float boxv7[3];

};
#endif

//
// End of DroneView.h .
//
