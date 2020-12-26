cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Modbuspp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

######## Sub-projects ##############

if (CMAKE_PLATFORM STREQUAL "UNIT-TEST")
add_subdirectory(Modbuspp)
add_subdirectory(UnitTests)
else()
add_subdirectory(Modbuspp)
endif()


