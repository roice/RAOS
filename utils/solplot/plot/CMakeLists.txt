#====================================================
# CMakeLists configuration file for plot lib of
# solplot project
# this file aims to build a lib calls plot to be
# further linked to the project
# 
# Author: Roice(LUO Bing)
# Date:   2014-11-26 Create this file

# include octave related
include_directories(/usr/include/octave-3.8.2)
include_directories(/usr/include/octave-3.8.2/octave)
include_directories(/usr/include/hdf5/serial)
# include rtklib related, so as to search for rtklib.h
include_directories(${PROJECT_SOURCE_DIR}/../../3rdparty/rtklib_2.4.2_p10/src)

add_library(plot plot_octave.cxx)
