/*
 * Callback functions implementation for the Panel part of SolutionPlot3D, 
 * which is an utility of FGCS_3DAO(FLTK Ground Control Station for Three 
 * Dimension Active Olfaction).
 * 
 * Author: Roice (LUO Bing)
 * Date: 2014-11-21 create this file
 */

#include <stdio.h>      // fprintf()
//#include <config.h>     // FLTK config file auto-generated
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/filename.H>		// fl_open_uri()

/* This callback is invoked whenever the user clicks an item on menu bar */
void SolPlotMenuCallback(Fl_Widget *w, void *)
{
    /* Get the menubar widget */
    Fl_Menu_Bar *bar = (Fl_Menu_Bar*)w;
    /* Get the menu item that was picked */
    const Fl_Menu_Item *item = bar->mvalue();
    /* Get full pathname of picked item */
    char ipath[256];
    bar->item_pathname(ipath, sizeof(ipath));
    /* Print item picked */
    fprintf(stderr, "callback: You picked '%s'", item->label());
    /* ..and full pathname */
    fprintf(stderr, ", item_pathname() is '%s'", ipath);
}
