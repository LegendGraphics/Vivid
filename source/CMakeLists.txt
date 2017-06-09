project(TinyEngine)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)

find_package(OpenGL REQUIRED)
#find_package(Boost REQUIRED COMPONENTS system filesystem chrono)
#find_package(lua REQUIRED)
find_package(3rdParty REQUIRED)

include_directories (${CMAKE_SOURCE_DIR}/source)
#include_directories(${Boost_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIR})
include_directories(${RAPID_XML_INCLUDE_DIR})
#include_directories(${SOIL_INCLUDE_DIR})
#include_directories(${LUA_INCLUDE_DIR})
#include_directories(${TOLUAPP_INCLUDE_DIR})

  
FILE( GLOB common               "common/*.*" ) 
FILE( GLOB math                 "math/*.*" )  
FILE( GLOB_RECURSE  renderer    "renderer/*.*") 
FILE( GLOB renderer_dir         "renderer/*.*") 
FILE( GLOB renderer_device      "renderer/device/*.*") 
FILE( GLOB renderer_runtime     "renderer/runtime/*.*") 
FILE( GLOB renderer_resource    "renderer/resource/*.*") 
FILE( GLOB base                 "base/*.*" ) 
FILE( GLOB io                   "io/*.*" )
FILE( GLOB shape                "shape/*.*" )
                     
source_group("common"               FILES ${common} )
source_group("math"                 FILES ${math} )
source_group("renderer"             FILES ${renderer_dir} )
source_group("renderer\\device"     FILES ${renderer_device} )
source_group("renderer\\runtime"    FILES ${renderer_runtime} )
source_group("renderer\\resource"   FILES ${renderer_resource} )
source_group("base"                 FILES ${base} )
source_group("io"                   FILES ${io} )
source_group("shape"                FILES ${shape} )


ADD_EXECUTABLE ( TinyEngine main.cpp ${common} ${math} ${renderer} ${base} ${io} ${shape})
target_link_libraries(TinyEngine ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${GLFW_LIBRARY})

