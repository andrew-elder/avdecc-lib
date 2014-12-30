#!/bin/bash
set -ev
rm -rf buld
mkdir build
cd build
cmake .. -G "Unix Makefiles"
make
