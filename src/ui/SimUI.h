#ifndef SimUI_H
#define SimUI_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Tabs.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>

class SimUI
{
public:
    SimUI(int width, int height, const char* title);
    //Fl_Double_Window *panel;
};

#endif
