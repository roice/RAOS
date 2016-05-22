/*
 * Main function of Simulator
 *
 * Author: Roice (LUO Bing)
 * Date: 2014-11-21 create this file (previous fgcsgdm)
 *       2016-02-01 create this file (RAOS)
 */

//#include <config.h>
#ifndef __APPLE__
    #if !HAVE_GL || !HAVE_GL_GLU_H
        #define ERROR_NO_GL_GLU_FOUND
    #endif
#endif

#include "FL/Fl.H"
#ifdef ERROR_NO_GL_GLU_FOUND
    #include <FL/fl_message.H>
#endif
#include "ui/SimUI.h" // control panel and GL view
#include "model/SimModel.h" // models
#include "SimConfig.h" // settings

/***************************************************************/
/**************************** MAIN *****************************/
/***************************************************************/

int main(int argc, char **argv) 
{
#ifndef ERROR_NO_GL_GLU_FOUND
    /* initialize sim settings */
    SimConfig_restore();

    /* initialize simulator stuff (quadrotor, plume, etc.) */
  	SimModel_init();
    
    // Create a window for simulation
    SimUI ui(800, 600, "Robot Active Olfaction Simulator");
    
    // Run
    Fl::run();

    // save configs before closing
    SimConfig_save();

    // delete events, free memory...
    SimModel_finish();
    return 0;
#else
    fl_alert("This demo does not work without GL and GLU");
    return 1;
#endif
}

/* End of SimMain.cxx */
