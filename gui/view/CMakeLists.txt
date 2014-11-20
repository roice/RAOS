set(EXECUTABLE_OUTPUT_PATH ${FLTK_BINARY_DIR}/bin/fgcsgdm)

#######################################################################
# audio libs for test apps
if(WIN32)
   set(AUDIOLIBS winmm)
elseif(APPLE)
   set(AUDIOLIBS "-framework CoreAudio")
elseif(HAVE_ALSA_ASOUNDLIB_H)
   set(AUDIOLIBS -lasound)
endif(WIN32)

#######################################################################
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  )

#######################################################################

# OpenGL demos...
if(OPENGL_FOUND)
    CREATE_EXAMPLE(DroneView "DroneMain.cxx;DroneView.cxx;DroneViewUI.fl" "fltk;fltk_gl")
endif(OPENGL_FOUND)
