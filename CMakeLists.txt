cmake_minimum_required(VERSION 3.16)

project(dkcoro)

option(USE_GCC_11 "use gcc-11" OFF)
option(USE_GCC_10 "use gcc-10" OFF)
option(USE_ASAN "use address sanitizer" OFF)

if(USE_GCC_11)
  message(STATUS "using gcc-11")
  set(CMAKE_C_COMPILER "gcc-11")
  set(CMAKE_CXX_COMPILER "g++-11")
elseif(USE_GCC_10)
  message(STATUS "using gcc-10")
  set(CMAKE_C_COMPILER "gcc-10")
  set(CMAKE_CXX_COMPILER "g++-10")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines")
else()
  message(STATUS "neither gcc-10 nor gcc-11 detected")
endif()

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

if(USE_ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fsanitize=address")
endif()

find_package(PkgConfig REQUIRED)

pkg_check_modules(GFLAGS REQUIRED gflags)
pkg_check_modules(LIBEVENT REQUIRED libevent)
pkg_check_modules(LIBGLOG REQUIRED libglog)
pkg_check_modules(LIBUV REQUIRED libuv)
pkg_check_modules(GTEST REQUIRED gtest)
pkg_check_modules(GTEST_MAIN REQUIRED gtest_main)
pkg_check_modules(GMOCK REQUIRED gmock)
pkg_check_modules(GMOCK_MAIN REQUIRED gmock_main)

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(dkcoro)
add_subdirectory(examples)

enable_testing()
add_subdirectory(test)
