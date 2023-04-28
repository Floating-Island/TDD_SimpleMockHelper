#!/usr/bin/bash

mkdir -p builds/windows
cd builds/windows
cmake -DCMAKE_TOOLCHAIN_FILE=../../TC-windows.cmake ../..
cmake --build .