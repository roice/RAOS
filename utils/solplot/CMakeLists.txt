cmake_minimum_required(VERSION 2.6)

# ================ User can Access ==================
# Project name
set(PRJ_NAME solplot)
# Add DEBUG defination to print out debug info
add_definitions(-DDEBUG)
# ===================================================



# ============= Don't touch the following ===========
project(${PRJ_NAME})
# if compile on Mac OSX, the "-framework Cocoa" flag should be added
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -framework Cocoa")
    message("Compile on APPLE MACOSX")
elseif(UNIX)
    message("Compile on UNIX")
endif()

# Set FLTK_DIR to the directory which contains FLTKConfig.cmake file
# The FLTK libs, headers,... are installed in "3rdparty/fltk-1.3.3/build/
#   install" directories
set(FLTK_DIR "${${PRJ_NAME}_SOURCE_DIR}/../../3rdparty/fltk-1.3.3/build")
# Set FLTK libraries path
set(FLTK_LIBRARIES "${${PRJ_NAME}_SOURCE_DIR}/../../3rdparty/fltk-1.3.3/build/lib/libfltk.a;${${PRJ_NAME}_SOURCE_DIR}/../../3rdparty/fltk-1.3.3/build/lib/libfltk_forms.a;${${PRJ_NAME}_SOURCE_DIR}/../../3rdparty/fltk-1.3.3/build/lib/libfltk_gl.a;${${PRJ_NAME}_SOURCE_DIR}/../../3rdparty/fltk-1.3.3/build/lib/libfltk_images.a")

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
target_link_libraries(solplot3d ${FLTK_LIBRARIES})
