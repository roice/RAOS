fltk_wrap_ui(DroneViewUI DroneViewUI.fl)
add_library(DroneViewUI DroneView.cxx ${DroneViewUI_FLTK_UI_SRCS})

add_executable(fgcsgdm DroneMain.cxx)
add_dependencies(fgcsgdm DroneViewUI)
target_link_libraries(fgcsgdm DroneViewUI)
target_link_libraries(fgcsgdm fltk)
#target_link_libraries(fgcsgdm ${FLTK_LIBRARIES})
#target_link_libraries(fgcsgdm ${OPENGL_LIBRARIES})
