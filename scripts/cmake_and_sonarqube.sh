#!/bin/sh

echo 'Cmake compilation and Sonarcloud scripts started...'
# Exit with nonzero exit code if anything fails
set -e


cd $TRAVIS_BUILD_DIR/Modbuspp
mkdir build
cd build
cmake -S ../Modbuspp/ -B .  -DCMAKE_BUILD_TYPE:String=Debug \
-DCMAKE_PLATFORM:String=POSIX -DPROJECT_TYPE:String=UNIT-TEST -DCMAKE_C_COMPILER:STRING=/usr/bin/gcc -DCMAKE_CXX_COMPILER:STRING=/usr/bin/g++ ..
cd ..


NUMBER_OF_PROCESSORS=$(nproc --all)

cmake --build build/ --target clean

build-wrapper-linux-x86-64 --out-dir bw_output  cmake  --build build/ --target all

sonar-scanner -Dproject.settings=$TRAVIS_BUILD_DIR/sonar-project.properties  -Dsonar.cfamily.threads=${NUMBER_OF_PROCESSORS}
