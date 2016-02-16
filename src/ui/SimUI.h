#ifndef SimUI_H
#define SimUI_H

/* FLTK */
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Tabs.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
/* OpenGL */
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <FL/glut.h>

class SimUI
{
public:
    SimUI(int width, int height, const char* title);
    //Fl_Double_Window *panel;
};

#endif
