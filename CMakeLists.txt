cmake_minimum_required(VERSION 2.8)
project (Vivid)
 
add_definitions(-DUSE_GL)
add_subdirectory(source/vivid)
add_subdirectory(bindings/python)
