####==================================================
#### Compile, Setup and install script of fgcsgdm
####==================================================

#!/bin/sh

# Get the absolute TOP path of this project
prjtop=$(cd "$(dirname "$0")"; pwd)
echo "Absolute path of project top directory is: "$prjtop
sleep 5

echo "Start Compiling 3d party soft ..."
echo "Start Compiling FLTK..."
sleep 1
##======== Compile 3rd Party softwares ========
# Compile fltk
cd $prjtop/3rdparty/fltk-1.3.3
mkdir -p build/install
cd build
cmake -D CMAKE_INSTALL_PREFIX=./install ..
make
make install

echo "Start Compiling RTKLIB..."
sleep 1
# Compile rtklib, after make, there will be librtk.a and librcv.a in the
# build directory
cd $prjtop/3rdparty/rtklib_2.4.2_p10
mkdir build
cd build
cmake ..
make

echo "Start Compiling utils"
sleep 5
##======== Compile utils ======================
# Compile SolPlot3D
cd $prjtop/utils/solplot
mkdir build
cd build
cmake ..
make
