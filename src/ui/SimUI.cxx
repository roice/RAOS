/*
 * User Interface of Simulator
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-01 create this file
 */

#include "SimUI.h"

SimUI::SimUI(int width, int height, const char* title=0)
{
    {
    Fl_Double_Window *panel = new Fl_Double_Window(width, height, title);
    panel->end();
    // Display the window
    panel->show();
    }
};
