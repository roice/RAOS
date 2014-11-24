/*
 * Callback functions implementation for the Panel part of SolutionPlot3D, 
 * which is an utility of FGCS_3DAO(FLTK Ground Control Station for Three 
 * Dimension Active Olfaction).
 * 
 * Author: Roice (LUO Bing)
 * Date: 2014-11-21 create this file
 */

#include <stdio.h>              // fprintf()
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/filename.H>		// fl_open_uri()


/* Functions... */
static void fc_callback(Fl_File_Chooser *, void *);

/* This callback is invoked whenever the user clicks File->Open File... */
void SolPlot_Menu_Callback(Fl_Widget *w, void *)
{
    Fl_File_Chooser *fc;

    /* Get the menubar widget */
    Fl_Menu_Bar *bar = (Fl_Menu_Bar*)w;
    /* Get the menu item that was picked */
    const Fl_Menu_Item *item = bar->mvalue();

#if(DEBUG)
    /* Get full pathname of picked item */
    char path_picked_item[256];
    bar->item_pathname(path_picked_item, sizeof(path_picked_item));
    /* Print item picked */
    fprintf(stderr, "Debug: You picked '%s'", item->label());
    /* ..and full pathname */
    fprintf(stderr, ", item_pathname() is '%s'\n", path_picked_item);
#endif

    /* if picked item is File->Open File... */
    if(0 == strcmp(item->label(), "Open File..."))
    {
#if(DEBUG)
        fprintf(stderr, "DEBUG: Start File Chooser\n");
#endif

        /* return absolute file path */
        char *file_abs_path = fl_file_chooser("Choose a solution file", "NEMA0183 (*.{nmea, nm})", ".", 0);
        if (file_abs_path != NULL)
        {
#if(DEBUG)
            fprintf(stderr, "file path is: %s", file_abs_path);
#endif
            SolPlot_LoadFile(file_abs_path,);
    }
}
/* Handle choices in the file chooser */
static void fc_callback(Fl_File_Chooser *fc, void *data)
{
    const char *filename;
#if(DEBUG)
    printf("DEBUG: fc_callback(fc = %p, data = %p)\n", fc, data);
#endif
    filename = fc->value();
#if(DEBUG)
    printf("DEBUG: filename = \"%s\"\n", filename ? filename : "null");
#endif
}
