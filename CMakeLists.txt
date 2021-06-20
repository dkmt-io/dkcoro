cmake_minimum_required(VERSION 3.19)
project(dkcoro)

set(CMAKE_C_COMPILER "gcc-11")
set(CMAKE_CXX_COMPILER "g++-11")

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GFLAGS REQUIRED gflags)
pkg_check_modules(LIBEVENT REQUIRED libevent)
pkg_check_modules(LIBGLOG REQUIRED libglog)
pkg_check_modules(LIBUV REQUIRED libuv)

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(dkcoro)
add_subdirectory(examples)
