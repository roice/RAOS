cmake_minimum_required(VERSION 2.6)

project(fgcsgdm)

set(FLTK_DIR /home/roice/Programs/fltk-1.3.3)

find_package(FLTK REQUIRED NO_MODULE)
#find_package(OpenGL REQUIRED)
include(${FLTK_USE_FILE})

add_subdirectory(src)
