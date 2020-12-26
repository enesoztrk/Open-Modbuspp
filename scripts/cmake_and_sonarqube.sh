#!/bin/sh

echo 'Cmake compilation and Sonarcloud scripts started...'
# Exit with nonzero exit code if anything fails
set -e


cd $TRAVIS_BUILD_DIR/Modbuspp
mkdir build
cd build
cmake -S ../Modbuspp/ -B . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE:String=Debug \
-DCMAKE_C_COMPILER:STRING=/usr/bin/gcc -DCMAKE_CXX_COMPILER:STRING=/usr/bin/g++


cmake --build $CMAKE_CACHE_PATH --target clean

build-wrapper-linux-x86-64 --out-dir bw_output  $CMAKE_PATH  --build build/ --target Modbuspp

sonar-scanner -Dproject.settings=$TRAVIS_BUILD_DIR/sonar-project.properties
