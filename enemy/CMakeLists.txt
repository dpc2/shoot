

aux_source_directory(. enemy_SRC)
#message(STATUS "SRC:-------------------- " ${SRC})
add_library(enemy ${enemy_SRC})
