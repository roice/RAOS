//
//

#include <config.h>
#include <FL/Fl.H>
#include "DroneViewUI.h"

int
main(int argc, char **argv) {

    DroneViewUI *cvui=new DroneViewUI;
    
//Initial global objects.
    
    Fl::visual(FL_DOUBLE|FL_INDEX);

    cvui->show(argc, argv);
    
    return Fl::run();
}


//
// End of DroneMain.cxx
//
