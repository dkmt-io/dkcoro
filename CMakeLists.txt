cmake_minimum_required(VERSION 3.19)
project(dkcoro)

set(CMAKE_C_COMPILER "gcc-11")
set(CMAKE_CXX_COMPILER "g++-11")

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(dkcoro)
add_subdirectory(examples)
