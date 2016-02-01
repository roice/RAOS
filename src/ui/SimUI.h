#ifndef SimUI_H
#define SimUI_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

class SimUI
{
public:
    SimUI(int width, int height, const char* title);
    Fl_Double_Window *panel;
};

#endif
