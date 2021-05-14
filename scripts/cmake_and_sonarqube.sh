#!/bin/sh

echo 'Cmake compilation and Sonarcloud scripts started...'
# Exit with nonzero exit code if anything fails
set -e


cd $TRAVIS_BUILD_DIR/Modbuspp
mkdir build
cd build
cmake   -DCMAKE_BUILD_TYPE:String=Debug \
-DCMAKE_PLATFORM:String=POSIX -DPROJECT_TYPE:String=UNIT-TEST -DSTATIC_LIB:String=ON ..


NUMBER_OF_PROCESSORS=$(nproc --all)



build-wrapper-linux-x86-64 --out-dir bw_output  make clean all
make 

$TRAVIS_BUILD_DIR/Modbuspp/UnitTests/bin/UnitTest
echo 'Gcov process started...'
mkdir gcov-coverage

for x in $TRAVIS_BUILD_DIR/Modbuspp/build/Modbuspp/CMakeFiles/Modbuspp.dir/src/*.cpp.o; do
  echo "x: $x"
  gcov "$x"
done

cd ..
sonar-scanner -Dproject.settings=$TRAVIS_BUILD_DIR/sonar-project.properties  -Dsonar.cfamily.threads=${NUMBER_OF_PROCESSORS} \
-Dsonar.cfamily.gcov.reportsPath="$TRAVIS_BUILD_DIR/Modbuspp/build"
