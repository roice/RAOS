####==================================================
#### Compile, Setup and install script of fgcsgdm
####==================================================

#!/bin/sh

# Get the absolute TOP path of this project
prjtop=$(cd "$(dirname "$0")"; pwd)
echo "Absolute path of project top directory is: "$prjtop
sleep 5

echo "Start Compiling ..."
sleep 1
##======== Compile 3rd Party softwares ========
# Compile fltk
cd $prjtop/3rdparty/fltk-1.3.3
mkdir -p build/install
cd build
cmake -D CMAKE_INSTALL_PREFIX=./install ..
make
make install
# Compile octave

##======== Compile utils ======================
# Compile SolPlot3D
cd $prjtop/utils/solplot
mkdir build
cd build
cmake ..
make
