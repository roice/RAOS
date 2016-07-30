#!/bin/bash
# Get the absolute path of this script
libsdir=$(cd "$(dirname "$0")"; pwd)
cd $libsdir
# Build FVM lib
python setup.py build_ext --inplace
