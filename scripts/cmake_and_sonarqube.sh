#!/bin/sh

echo 'Cmake compilation and Sonarcloud scripts started...'
# Exit with nonzero exit code if anything fails
set -e




$CMAKE_PATH  --build $CMAKE_CACHE_PATH --target clean

build-wrapper-linux-x86-64 --out-dir $(pwd)/bw_output  $CMAKE_PATH  --build $CMAKE_CACHE_PATH --target Modbuspp

sonar-scanner -Dproject.settings=$TRAVIS_BUILD_DIR/sonar-project.properties
