####=================================
#### Uninstall all build files
####=================================

#!/bin/sh

# Get project top directory abs path
prjtop=$(cd "$(dirname "$0")"; pwd)
echo "Absolute path of project top directory is: "$prjtop
sleep 2

echo "Start cleaning ..."
sleep 1
# clear 3rd party software builds
echo "Cleaning FLTK..."
cd $prjtop/3rdparty
rm -rf fltk-1.3.3/build

# clear blas
echo "Cleaning BLAS..."
cd $prjtop/3rdparty/blas/BLAS-3.6.0
make clean
rm *.a

# clear CBLAS
echo "Cleaning CBLAS..."
cd $prjtop/3rdparty/blas/CBLAS
make clean
rm lib/*.a

# clear RAOS builds
echo "Cleaning RAOS..."
cd $prjtop
rm -rf build

echo "Uninstall done"
