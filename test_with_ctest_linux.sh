#!/usr/bin/bash

cd builds/linux
ctest --progress --output-junit ../../junit_report.xml --rerun-failed --output-on-failure