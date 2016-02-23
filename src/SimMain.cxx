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
#include "SimUI.h" // control panel and GL view
#include "SimModel.h" // models

/***************************************************************/
/**************************** MAIN *****************************/
/***************************************************************/

int main(int argc, char **argv) 
{
    /* initialize simulator stuff (quadrotor, plume, etc.) */
  	SimModel_init();
    
    // Create a window for simulation
    SimUI ui(800, 600, "Robot Active Olfaction Simulation");
    
    // Run and return    
    return Fl::run();
}

#endif

/* End of SimMain.cxx */
