####==================================================
#### Compile, Setup and install script of RAOS
####                For Linux, MacOS
####==================================================

#!/bin/sh

# Get platform type
if [ "$(uname)" = "Darwin" ]; then
    # Do something under Mac OS X platform
    SYSTEM="APPLE"
elif [ "$(expr substr $(uname -s) 1 5)" = "Linux" ]; then
    # Do something under GNU/Linux platform
    SYSTEM="LINUX"
elif [ "$(expr substr $(uname -s) 1 10)" = "MINGW32_NT" ]; then
    # Do something under Windows NT platform
    SYSTEM="WIN32"
fi

# Get the absolute TOP path of this project
prjtop=$(cd "$(dirname "$0")"; pwd)
echo "Absolute path of project top directory is: "$prjtop
sleep 1

##======== Compile 3rd Party softwares ========
echo "Start Compiling 3d party soft ..."
# Compile fltk
if [ ${SYSTEM} = "LINUX" ]; then
    echo "Start Compiling FLTK..."
    sleep 1
    cd $prjtop/3rdparty
    tar xzvf fltk-1.3.4-1-source.tar.gz
    cd fltk-1.3.4-1
    mkdir -p build/install
    cd build
    cmake -D CMAKE_INSTALL_PREFIX=./install ..
    make
    make install
fi
# Compile blas
echo "Start Compiling BLAS..."
sleep 1
cd $prjtop/3rdparty/blas/BLAS-3.6.0
make
mv blas_*.a libblas.a
rm ./*.o  # cleanup
# Compile cblas
echo "Start Compiling CBLAS..."
sleep 1
cd $prjtop/3rdparty/blas/CBLAS
make
mv lib/cblas_*.a lib/libcblas.a
#   cleanup
rm ./src/*.o
rm ./testing/*.o
rm ./testing/x*
# Compile lapack
echo "Start Compiling LAPACK..."
sleep 1
cd $prjtop/3rdparty/lapack-3.7.0
mkdir build
cd build
cmake -DLAPACKE=ON ..
make

##======== Compile RAOS ========
echo "Start Compiling RAOS..."
sleep 1
cd $prjtop
mkdir build
cd build
cmake ..
make
#make install
