/*
 * Main function of Simulator
 *
 * Author: Roice (LUO Bing)
 * Date: 2014-11-21 create this file (previous fgcsgdm)
 *       2016-02-01 create this file (RAOS)
 *       2017-07-19 modify this file for RAOS v2.0
 */

#include "FL/Fl.H"
#include "ui/RAOS_UI.h" // control panel and GL view
#include "RAOS_config.h" // RAOS settings

/***************************************************************/
/**************************** MAIN *****************************/
/***************************************************************/

int main(int argc, char **argv) 
{
    /* initialize sim settings */
    RAOS_config_restore(); 
    
    // Create a window to display simulation result
    new RAOS_UI(800, 600, "Robot Active Olfaction Simulator");
    
    // Run
    Fl::run();

    // save configs before closing
    RAOS_config_save();
    
    return 0;
}

/* End of main.cxx */
