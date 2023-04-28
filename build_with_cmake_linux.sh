#!/usr/bin/bash

mkdir -p builds/linux
cd builds/linux
cmake -DCMAKE_TOOLCHAIN_FILE=../../TC-linux.cmake ../..
cmake --build .