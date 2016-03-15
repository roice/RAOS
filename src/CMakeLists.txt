#====================================================
# CMakeLists configuration file for RAOS project
# this file aims to build the RAOS project
# 
# Author: Roice(LUO Bing)
# Date:   2014-11-24 Create this file (previous solplot3d)
#         2016-02-01 Re-create this file
cmake_minimum_required(VERSION 2.8)

#====================================================
# ================ User can Access ==================
#====================================================
# install path
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
# Project name
set(PRJ_NAME RAOS)
# Debug version
set(CMAKE_BUILD_TYPE Debug)
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
    # Modified by Roice, 20160308
    # As CUDA is used to compute helicopter wakes, the MacOSX platform will
    #  no longer to be supported since March 8, 2016. Currently the RAOS
    #  project is written on Linux, but it may be compiled on Windows as well
    message("Compile on APPLE MACOSX")
    message(FATAL_ERROR "The RAOS project only support Linux and Windows OS with graphic cards.")
elseif(UNIX)
    message("Compile on UNIX")
endif()

#$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#============== Find Dependencies ================
#$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#---- External FLTK related settings ----
# Set FLTK_DIR to the directory which contains FLTKConfig.cmake file
set(FLTK_DIR "${PROJECT_SOURCE_DIR}/../3rdparty/fltk-1.3.3/build")
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

#---- External CUDA related settings ----
find_package(CUDA REQUIRED)
# nvcc flags
set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-gencode arch=compute_50,code=sm_50;-G)

#$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#============== Build the project ================
#$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



#---- source files include path settings ----
# add source directory into include path
#   add root dir to search for header files of RAOS projects
include_directories(${PROJECT_SOURCE_DIR})
#   add cblas dir to search for cblas.h header for linear algebra
include_directories(${PROJECT_SOURCE_DIR}/../3rdparty/blas/CBLAS/include)

#---- library files path settings ----
# add library dir into lib path
#   add fltk lib directory
link_directories(${PROJECT_SOURCE_DIR}/../3rdparty/fltk-1.3.3/build/lib)
#   add blas and cblas lib dir
link_directories(${PROJECT_SOURCE_DIR}/../3rdparty/blas/BLAS-3.6.0)
link_directories(${PROJECT_SOURCE_DIR}/../3rdparty/blas/CBLAS/lib)

#---- start compiling ----
set(LIB_UI_NAME ui)
set(LIB_MODEL_NAME model) # models
# make a library from quadrotor model files
cuda_add_library(${LIB_MODEL_NAME} 
    model/SimModel.cxx
    model/plume.cxx
    model/wake_rotor.cxx model/wake.cu
    model/robot.cxx model/quadrotor.cxx)
# make a library from ui files
add_library(${LIB_UI_NAME} ui/SimUI.cxx ui/SimView.cxx ui/agv.cxx
    ui/draw/DrawScene.cxx ui/draw/materials.cxx 
    ui/draw/draw_robots.cxx ui/draw/draw_qr.cxx
    ui/draw/draw_arena.cxx ui/draw/draw_plume.cxx
    ui/draw/draw_wake.cxx)
# compile main file
add_executable(${PRJ_NAME} SimMain.cxx SimLoop.cxx SimConfig.cxx)
add_dependencies(${PRJ_NAME} ${LIB_MODEL_NAME} ${LIB_UI_NAME})

#---- start linking ----
# Note: the former line depends on the next line
# link model library created above
target_link_libraries(${PRJ_NAME} ${LIB_MODEL_NAME})
# link GUI library created above
target_link_libraries(${PRJ_NAME} ${LIB_UI_NAME})
# link external FLTK library
target_link_libraries(${PRJ_NAME} fltk)
# link external OpenGL library
target_link_libraries(${PRJ_NAME} fltk_gl)
# link external image library
target_link_libraries(${PRJ_NAME} fltk_images)
# link external blas library
target_link_libraries(${PRJ_NAME} cblas)
target_link_libraries(${PRJ_NAME} blas)
target_link_libraries(${PRJ_NAME} gfortran)

# install
#install(TARGETS ${PRJ_NAME}
#    RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/../bin
#    LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/../lib
#    )
