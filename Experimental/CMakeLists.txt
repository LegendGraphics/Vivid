project(Experimental)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

FILE( GLOB Reflection 			  		"Reflection/*.*" ) 
					 
source_group("Reflection" 			FILES ${Reflection} )

include_directories (${Reflection})

ADD_EXECUTABLE ( Experimental main.cpp ${Reflection})
target_link_libraries(Experimental)

