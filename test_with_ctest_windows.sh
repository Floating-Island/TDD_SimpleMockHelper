#!/usr/bin/bash

cd builds/windows
WINEPREFIX=/usr/wine/.wine xvfb-run -a wine cmake ctest_test --progress --output-junit ../../junit_report.xml