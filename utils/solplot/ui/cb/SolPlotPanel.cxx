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
#include "ufrtk.h"             // RTK related functions of this project
#include "plot.h"               // plot functions

/* Functions... */
static void SolPlot_LoadFilePlot(char *files[], int nfile);

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
    fprintf(stderr, "DEBUG: You picked '%s'", item->label());
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
        char *file_abs_path[MAXNFILE];
        file_abs_path[0] = fl_file_chooser("Choose a solution file", "NEMA0183 (*.{nmea, nm})", ".", 0);
        if (file_abs_path != NULL)
        {
#if(DEBUG)
            fprintf(stderr, "DEBUG: Selected file path is: %s\n", file_abs_path[0]);
#endif
            SolPlot_LoadFilePlot(file_abs_path, 1);
        }
    }
}

/* Load solution file and plot */
static void SolPlot_LoadFilePlot(char *files[], int nfile)
{
    /* solution buffer structure */
    solbuf_t sol={0};
    /* solution file path array */
    char *paths[MAXNFILE];
    int i,n=0;

    /* Get paths of all of the solution files */
    for (i=0; i<nfile; i++) paths[i]=files[i];

#if(DEBUG)
    for (i=0; i<nfile; i++)
    {
        fprintf(stderr, "DEBUG: These files will be loaded: \n");
        fprintf(stderr, "       (%d) %s\n", i, paths[i]);
    }
#endif

    /* read and decode file */
    if(!ReadSolutionFiles(paths, nfile, &sol))
    {
        for(i=0; i<nfile; i++)
        {
            fprintf(stderr, "ERROR: No solution data: %s", paths[i]);
        }
    }
    else
    {
#if(DEBUG)
        fprintf(stderr, "DEBUG: Decoded solution sol.data[0]->rr[0] == %f\n", sol.data[0].rr[0]);
        fprintf(stderr, "DEBUG: Decoded solution sol.data[0]->rr[1] == %f\n", sol.data[0].rr[1]);
        fprintf(stderr, "DEBUG: Decoded solution sol.data[0]->rr[2] == %f\n", sol.data[0].rr[2]);
        fprintf(stderr, "DEBUG: sol.data[0]->type == %d\n", sol.data[0].type);
        fprintf(stderr, "DEBUG: Max number of solution: %d\n", sol.n);
        fprintf(stderr, "DEBUG: Max number of buffer: %d\n", sol.nmax);
        fprintf(stderr, "DEBUG: Decoded solution sol.data[%d]->rr[0] == %f\n", sol.n -1, sol.data[sol.n-1].rr[0]);
        fprintf(stderr, "DEBUG: Decoded solution sol.data[%d]->rr[1] == %f\n", sol.n -1, sol.data[sol.n-1].rr[1]);
        fprintf(stderr, "DEBUG: Decoded solution sol.data[%d]->rr[2] == %f\n", sol.n -1, sol.data[sol.n-1].rr[2]);
#endif
        /* plot solutions with octave */
        plotRTKtraj3d(&sol);

    }
}

