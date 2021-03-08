

cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_COMPILER "g++" )						 
set(CMAKE_CXX_FLAGS "-std=gnu++2a -Wall -g -O0")	 
#set(CMAKE_CXX_FLAGS_DEBUG "-O0" ) 					 
#set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG " )  

#set(CMAKE_SOURCE_DIR .)
#set(PROJECT_SOURCE_DIR .)
#set(CMAKE_INSTALL_RPATH ${ROOTFS}/lib)
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#set(CMAKE_SKIP_RPATH FALSE)
#set(CMAKE_SKIP_BUILD_RPATH FALSE)
#set(CMKAE_SKIP_INSTALL_RPATH FALSE)

project(shoot)

include_directories(. object gui enemy rocket player)			 
link_libraries(GL GLU glut m pthread )					# all targets link with the same set of libs	

aux_source_directory(. SRC)
#message(STATUS "SRC:-------------------- " ${SRC})

add_subdirectory(object)
add_subdirectory(gui)
add_subdirectory(enemy)
add_subdirectory(rocket)
add_subdirectory(player)

link_libraries(object gui enemy rocket player)
add_executable(shoot ${SRC})


#target_link_libraries(cpp ?)	
#install(TARGETS a 
#	DESTINATION ${ROOTFS}/bin)
#install(FILES ${PROJECT_SOURCE_DIR}/ta.h 
#	DESTINATION ${ROOTFS}/include)

#message(STATUS "PROJECT_SOURCE_DIR:-------------------- " ${PROJECT_SOURCE_DIR})

#set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#option(USE_DATA "Use provided data implementation" ON)
#if(USE_DATA)
#	include_directories("${PROJECT_SOURCE_DIR}/data")
#	add_subdirectory(data)  
#	set(LIBS ${LIBS} data GL GLU glut m pthread input udev evdev)	
#else(USE_DATA)
#	message(ERROR "data not included")
#endif(USE_DATA)

#FIND_PACKAGE(libdb_cxx REQUIRED)
#MARK_AS_ADVANCED(LIBDB_CXX_INCLUDE_DIR LIBDB_CXX_LIBRARIES)
#if(LIBDB_CXX_INCLUDE_DIR AND LIBDB_CXX_LIBRARIES)
#	message(STATUS "Found libdb libraries")
#	INCLUDE_DIRECTORIES(${LIBDB_CXX_INCLUDE_DIR})
#	message(${LIBDB_CXX_LIBRARIES})
#	TARGET_LINK_LIBRARIES(ct ${LIBDB_CXX_LIBRARIES})
#else(LIBDB_CXX_INCLUDE_DIR AND LIBDB_CXX_LIBRARIES)
#	message(STATUS "NOT found libdb libraries")
#endif(LIBDB_CXX_INCLUDE_DIR AND LIBDB_CXX_LIBRARIES)

#cmake -DCMAKE_BUILD_TYPE=Debug（或Release），需要编译不同版本时进入不同目录执行make即可
#SET(CMAKE_MODULE_PATH ${CMAKE_ROOT}/Modules ${CMAKE_SOURCE_DIR}/cmake/modules)
# The version number.
#set (Tutorial_VERSION_MAJOR 1)
#set (Tutorial_VERSION_MINOR 0)
 







