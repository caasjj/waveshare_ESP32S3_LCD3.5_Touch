#!/bin/sh
# Run build.sh to generate a build.log file in build directory, for build level debugging
idf.py build "$@" > build/build.log 2>&1
