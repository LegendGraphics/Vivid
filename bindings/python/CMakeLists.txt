project(PyTinyEngine)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake)

find_package(PythonLibs)
find_package(3rdParty REQUIRED)
include_directories(${PYBIND11_INCLUDE_DIR})
include_directories(${PYTHON_INCLUDE_DIR})

FILE( GLOB pybind_cpp               "*.cpp*" ) 

add_subdirectory(pybind11)
pybind11_add_module(PyTinyEngine ${pybind_cpp})
target_link_libraries(PyTinyEngine ${PYTHON_LIBRARIES})

