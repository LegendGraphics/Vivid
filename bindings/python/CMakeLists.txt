project(PyVivid)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake)

find_package(PythonLibs)
set(PYBIND11_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/pybind11/include)

include_directories(${PYBIND11_INCLUDE_DIR})
include_directories(${PYTHON_INCLUDE_DIR})
include_directories (${VIVID_INCLUDE_DIR})



FILE( GLOB pybind_cpp               "*.cpp*" ) 

add_subdirectory(pybind11)
pybind11_add_module(PyVivid ${pybind_cpp})
target_link_libraries(PyVivid ${PYTHON_LIBRARIES} Vivid)
set_target_properties(PyVivid PROPERTIES SUFFIX ".pvd")

