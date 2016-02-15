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
cd $prjtop/3rdparty
rm -rf fltk-1.3.3/build
rm -rf rtklib_2.4.2_p10/build

# clear RAOS builds
cd $prjtop/src
rm -rf build

# clear utils builds
cd $prjtop/utils
rm -rf solplot/build

echo "Uninstall done"
