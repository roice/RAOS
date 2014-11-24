cmake_minimum_required(VERSION 2.6)

# ================ User can Access ==================
# Project name
set(PRJ_NAME rtklib)
# ===================================================

project(${PRJ_NAME})

#======== add sources ========
# add the path of rtklib.h
include_directories(${${PRJ_NAME}_SOURCE_DIR}/src)
# set the rtklib sources to build librtk
aux_source_directory(${${PRJ_NAME}_SOURCE_DIR}/src RTKLIB_SOURCES)
# set the receiver sources to build librcv
#aux_source_directory(${${PRJ_NAME}_SOURCE_DIR}/src/rcv RTKLIB_RCV_SOURCES)
set(RTKLIB_RCV_SOURCES ${${PRJ_NAME}_SOURCE_DIR}/src/rcv/skytraq.c ${${PRJ_NAME}_SOURCE_DIR}/src/rcv/novatel.c ${${PRJ_NAME}_SOURCE_DIR}/src/rcv/ublox.c ${${PRJ_NAME}_SOURCE_DIR}/src/rcv/ss2.c ${${PRJ_NAME}_SOURCE_DIR}/src/rcv/crescent.c ${${PRJ_NAME}_SOURCE_DIR}/src/rcv/gw10.c ${${PRJ_NAME}_SOURCE_DIR}/src/rcv/javad.c)

#======== set definitions ========
add_definitions("-Wall -O3 -ansi -pedantic")
# enable GLONASS Galileo QZSS BeiDou
add_definitions(-DENAGLO -DENAGAL -DENAQZS -DENACMP)
# set number of obs codes/frequencies
add_definitions(-DNFREQ=3)
# set number of extended obs codes
add_definitions(-DNEXOBS=3)
# enable QZSS LEX extension
add_definitions(-DEXTLEX)

#======== make libraries ========
# librtk.a: build from rtklib sources src/*.c
# librcv.a: build from receiver sources src/rcv/*.c
add_library(rtk ${RTKLIB_SOURCES})
add_library(rcv ${RTKLIB_RCV_SOURCES})
