

aux_source_directory(. gui_SRC)
#message(STATUS "SRC:-------------------- " ${SRC})
add_library(gui ${gui_SRC})
