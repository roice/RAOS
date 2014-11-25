#====================================================
# CMakeLists configuration file for solplot project
# this file aims to build a utility calls solplot3d
# 
# Author: Roice(LUO Bing)
# Date:   2014-11-24 Create this file
cmake_minimum_required(VERSION 2.6)

# ================ User can Access ==================
# Project name
set(PRJ_NAME solplot)
# Add DEBUG defination to print out debug info
add_definitions(-DDEBUG)
# ===================================================

# ============= Don't touch the following ===========
project(${PRJ_NAME})
#======== Detect which platform in use ========
# if compile on Mac OSX, the "-framework Cocoa" flag should be added
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -framework Cocoa")
    message("Compile on APPLE MACOSX")
elseif(UNIX)
    message("Compile on UNIX")
endif()

#======== FLTK related ========
# Set FLTK_DIR to the directory which contains FLTKConfig.cmake file
# The FLTK libs, headers,... are installed in "3rdparty/fltk-1.3.3/build/
#   install" directories
set(FLTK_DIR "${${PRJ_NAME}_SOURCE_DIR}/../../3rdparty/fltk-1.3.3/build")

# print out paths in order to check if goes wrong
message("Project Source Dir: \"${${PRJ_NAME}_SOURCE_DIR}\"")
message("Project Binary Dir: \"${${PRJ_NAME}_BINARY_DIR}\"")
message("FLTK_DIR (where the FLTKConfig.cmake file is): \"${FLTK_DIR}\"")
message("FLTK_LIBRARIES: \"${FLTK_LIBRARIES}\"")

# find the FLTK package
# "NO_MODULE" tells CMake to search only for the FLTKConfig file, not using
# the FindFLTK.cmake supplied with CMake, which doesn't work with this version
# of FLTK
find_package(FLTK REQUIRED NO_MODULE)
find_package(OpenGL REQUIRED)
# this file is in the same folder as FLTKConfig.cmake file
include(${FLTK_USE_FILE})

#======== source files ========
# add source directory into include path
# add project source dir to search for header files
include_directories(${${PRJ_NAME}_SOURCE_DIR})
# add rtklib header dir to search for rtklib.h file
include_directories(${${PRJ_NAME}_SOURCE_DIR}/../../3rdparty/rtklib_2.4.2_p10/src)
# add octave header dir to search for octave/oct.h file
include_directories(/usr/include/octave-3.8.2)

#======== library files ========
# add library dir into lib path
# add fltk lib directory
link_directories(${${PRJ_NAME}_SOURCE_DIR}/../../3rdparty/fltk-1.3.3/build/lib)
# add rtklib lib directory
link_directories(${${PRJ_NAME}_SOURCE_DIR}/../../3rdparty/rtklib_2.4.2_p10/build)

#======== start building ========
# convert GUI *.fl ui file to *.cxx and *.h files
fltk_wrap_ui(SolPlotUI SolPlotUI.fl)
add_library(SolPlotUI SolPlotPanel.cxx ${SolPlotUI_FLTK_UI_SRCS})
# compile
add_executable(solplot3d SolPlotMain.cxx)
add_dependencies(solplot3d SolPlotUI)

# link GUI library created above
target_link_libraries(solplot3d SolPlotUI)
# link FLTK library in the 3rdparty dir
target_link_libraries(solplot3d fltk)
# link RTKLIB library in the 3rdparty dir
target_link_libraries(solplot3d rtk)
#target_link_libraries(solplot3d fltk_gl)
