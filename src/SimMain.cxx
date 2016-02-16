/*
 * Main function of Simulator
 *
 * Author: Roice (Bing LUO)
 * Date: 2014-11-21 create this file (previous fgcsgdm)
 *       2016-02-01 create this file (RAOS)
 */

#include "FL/Fl.H"
#include "SimUI.h" // control panel and GL view

int main(int argc, char **argv) 
{
    // Create a window for simulation
    SimUI ui(1000, 600, "Robot Active Olfaction Simulation");
    // Run and return    
    return Fl::run();
}

/* End of SimMain.cxx */
