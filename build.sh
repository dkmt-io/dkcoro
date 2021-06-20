#!/bin/sh

export CMAKE_PREFIX_PATH=$(brew --prefix)

cmake -B output .
cmake --build output
