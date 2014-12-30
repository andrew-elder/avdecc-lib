#!/bin/bash
set -ev
rm -rf build
mkdir build
cd build
cmake .. -G "Unix Makefiles"
make
