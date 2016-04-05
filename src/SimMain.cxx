/*
 * Main function of Simulator
 *
 * Author: Roice (LUO Bing)
 * Date: 2014-11-21 create this file (previous fgcsgdm)
 *       2016-02-01 create this file (RAOS)
 */

#include <config.h>
#if !HAVE_GL || !HAVE_GL_GLU_H
#include <FL/Fl.H>
#include <FL/fl_message.H>
int main(int, char**) {
  fl_alert("This demo does not work without GL and GLU");
  return 1;
}
#else
// end of added block

#include "FL/Fl.H"
#include "ui/SimUI.h" // control panel and GL view
#include "model/SimModel.h" // models
#include "SimConfig.h" // settings

/***************************************************************/
/**************************** MAIN *****************************/
/***************************************************************/

int main(int argc, char **argv) 
{
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
}

#endif

/* End of SimMain.cxx */
