

aux_source_directory(. rocket_SRC)
#message(STATUS "SRC:-------------------- " ${SRC})
add_library(rocket ${rocket_SRC})
