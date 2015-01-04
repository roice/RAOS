#====================================================
# CMakeLists configuration file for solplot project
# this file aims to build a utility calls solplot3d
# 
# Author: Roice(LUO Bing)
# Date:   2014-11-24 Create this file
cmake_minimum_required(VERSION 2.6)

#====================================================
# ================ User can Access ==================
#====================================================
# install path
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
# Project name
set(PRJ_NAME solplot)
# Add DEBUG defination to print out debug info
add_definitions(-DDEBUG)
# ===================================================

#====================================================
# ============= Don't touch the following ===========
#====================================================
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

#$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#======== Build plot functions to a static library =======
#$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

# build plot functions
add_subdirectory(plot)

#$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#============== Build rest of the project ================
#$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

#---- External RTKLIB related settings ----
#add rtklib header dir to search for rtklib.h file
include_directories(${PROJECT_SOURCE_DIR}/../../3rdparty/rtklib_2.4.2_p10/src)

#---- External FLTK related settings ----
# Set FLTK_DIR to the directory which contains FLTKConfig.cmake file
set(FLTK_DIR "${PROJECT_SOURCE_DIR}/../../3rdparty/fltk-1.3.3/build")
# print out paths in order to check if goes wrong
message("Project Source Dir: \"${PROJECT_SOURCE_DIR}\"")
message("Project Binary Dir: \"${PROJECT_BINARY_DIR}\"")
message("FLTK_DIR (where the FLTKConfig.cmake file is): \"${FLTK_DIR}\"")
# find the FLTK package
# "NO_MODULE" tells CMake to search only for the FLTKConfig file, not using
# the FindFLTK.cmake supplied with CMake, which doesn't work with this version
# of FLTK
find_package(FLTK REQUIRED NO_MODULE)
find_package(OpenGL REQUIRED)
# this file is in the same folder as FLTKConfig.cmake file
include(${FLTK_USE_FILE})

#---- source files include path settings ----
# add source directory into include path
# add user interface and callback source dir to search for header files
#include_directories(${PROJECT_SOURCE_DIR}/ui)
include_directories(${PROJECT_SOURCE_DIR}/ui/cb)
# add sol dir of this project to search for RTK related functions
include_directories(${PROJECT_SOURCE_DIR}/sol)
# add plot dir of this project to search for plot.h
include_directories(${PROJECT_SOURCE_DIR}/plot)

#---- library files path settings ----
# add library dir into lib path
# add fltk lib directory
link_directories(${PROJECT_SOURCE_DIR}/../../3rdparty/fltk-1.3.3/build/lib)
# add rtklib lib directory
link_directories(${PROJECT_SOURCE_DIR}/../../3rdparty/rtklib_2.4.2_p10/build)
# add octave lib directory
link_directories(/usr/lib/x86_64-linux-gnu)

#---- start compiling ----
# convert GUI *.fl ui file to *.cxx and *.h files
set(LIB_UI_NAME ui)
fltk_wrap_ui(${LIB_UI_NAME} ui/SolPlotUI.fl)
# make a library from ui files
add_library(${LIB_UI_NAME} sol/ufrtk.c ui/cb/SolPlotPanel.cxx ${${LIB_UI_NAME}_FLTK_UI_SRCS})
# compile main file
add_executable(${PRJ_NAME} SolPlotMain.cxx)
add_dependencies(${PRJ_NAME} ${LIB_UI_NAME})
add_dependencies(${PRJ_NAME} plot)

#---- start linking ----
# Note: the former line depends on the next line
# link GUI library created above
target_link_libraries(${PRJ_NAME} ${LIB_UI_NAME})
# link plot library created above
target_link_libraries(${PRJ_NAME} plot)
# link external FLTK library
target_link_libraries(${PRJ_NAME} fltk)
# link external OpenGL library
#target_link_libraries(${PRJ_NAME} fltk_gl)
# link external rtklib library
target_link_libraries(${PRJ_NAME} rtk)
# link external octave library
target_link_libraries(${PRJ_NAME} octinterp)
target_link_libraries(${PRJ_NAME} octave)

# install
install(TARGETS ${PRJ_NAME}
    RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
    LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib
    ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib
    )
