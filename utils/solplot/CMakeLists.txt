cmake_minimum_required(VERSION 2.6)

# Project name
set(PRJ_NAME solplot)
project(${PRJ_NAME})

# Set FLTK_DIR to the directory which contains FLTKConfig.cmake file
# The FLTK libs, headers,... are installed in "3rdparty/fltk-1.3.3/build/
#   install" directories
set(FLTK_DIR "${${PRJ_NAME}_SOURCE_DIR}/../../3rdparty/fltk-1.3.3/build/install/lib/fltk")

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
# this file is in the same folder as FLTKConfig.cmake file
include(${FLTK_USE_FILE})

# add source directory into include path
include_directories("${${PRJ_NAME}_SOURCE_DIR}")

# convert GUI *.fl ui file to *.cxx and *.h files
fltk_wrap_ui(SolPlotUI SolPlotUI.fl)
add_library(SolPlotUI SolPlotPanel.cxx ${SolPlotUI_FLTK_UI_SRCS})

add_executable(solplot3d SolPlotMain.cxx)
add_dependencies(solplot3d SolPlotUI)

target_link_libraries(solplot3d SolPlotUI)
target_link_libraries(solplot3d fltk)
