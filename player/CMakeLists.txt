

aux_source_directory(. player_SRC)
#message(STATUS "SRC:-------------------- " ${SRC})
add_library(player ${player_SRC})
