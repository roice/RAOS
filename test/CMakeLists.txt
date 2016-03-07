#====================================================
# CMakeLists configuration file for testing
# this file aims to build the testing routines
# 
# Author: Roice(LUO Bing)
# Date: 2016-03-04 Create this file
cmake_minimum_required(VERSION 2.6)

#====================================================
# ================ User can Access ==================
#====================================================
# Project name
set(PRJ_NAME wake)
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
#   add blas and cblas lib dir
link_directories(${PROJECT_SOURCE_DIR}/../3rdparty/blas/BLAS-3.6.0)

#---- start compiling ----
# compile main file
add_executable(${PRJ_NAME} model/wake_rotor_cpu.cxx)

#---- start linking ----
# Note: the former line depends on the next line
# link external blas library
target_link_libraries(${PRJ_NAME} cblas)
target_link_libraries(${PRJ_NAME} blas)

# install
#install(TARGETS ${PRJ_NAME}
#    RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/../bin
#    LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/../lib
#   )
