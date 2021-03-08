

aux_source_directory(. object_src)
#message(STATUS "SRC:-------------------- " ${SRC})

add_library(object ${object_src})
