#!/usr/bin/bash

cd builds/windows
WINEPREFIX=/usr/wine/.wine xvfb-run -a wine 'C:\Program Files\CMake\bin\ctest.exe' --progress --output-junit ../../junit_report.xml --rerun-failed --output-on-failure