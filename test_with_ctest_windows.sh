#!/usr/bin/bash

cd builds/windows
WINEPREFIX=/usr/wine/.wine xvfb-run -a wine ctest --progress --output-junit ../../junit_report.xml