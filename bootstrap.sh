#!/bin/sh

if command -v brew 1>/dev/null 2>/dev/null; then
echo "homebrew detected"
export CMAKE_PREFIX_PATH=$(brew --prefix)
fi

if command -v gcc-11 1>/dev/null 2>/dev/null; then
echo "gcc-11 detected"
export USE_GCC_11=1
fi

if command -v gcc-10 1>/dev/null 2>/dev/null; then
echo "gcc-10 detected"
export USE_GCC_10=1
fi

cmake                      \
  -DUSE_GCC_11=$USE_GCC_11 \
  -DUSE_GCC_10=$USE_GCC_10 \
  -DCMAKE_BUILD_TYPE=Debug \
  -B build_debug .
cmake --build build_debug

cmake                        \
  -DUSE_GCC_11=$USE_GCC_11   \
  -DUSE_GCC_10=$USE_GCC_10   \
  -DCMAKE_BUILD_TYPE=Release \
  -B build_release .
cmake --build build_release

cmake                      \
  -DUSE_GCC_11=$USE_GCC_11 \
  -DUSE_GCC_10=$USE_GCC_10 \
  -DCMAKE_BUILD_TYPE=Debug \
  -DUSE_ASAN=1             \
  -B build .
cmake --build build

cd build
ctest
cd ..
