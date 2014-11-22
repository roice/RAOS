/*
 * Main function of SolutionPlot3D
 * which is an utility of FGCS_3DAO(FLTK Ground Control Station for Three 
 * Dimension Active Olfaction).
 *
 * Author: Roice (Bing LUO)
 * Date: 2014-11-21 create this file
 */

#include <FL/Fl.H>
#include "SolPlotUI.h"

int main(int argc, char **argv) 
{
    SolPlotUI *spui=new SolPlotUI;
    
    Fl::visual(FL_DOUBLE|FL_INDEX);

    spui->ControlPanel->show(argc, argv);
    
    return Fl::run();
}

/* End of SolPlotMain.cxx */
