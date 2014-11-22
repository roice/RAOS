#!/bin/sh
cd 3rdparty/fltk-1.3.3
mkdir -p build/install
cd build
cmake -D CMAKE_INSTALL_PREFIX=./install ..
make
make install

