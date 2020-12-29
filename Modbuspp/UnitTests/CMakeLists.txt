project(UnitTest CXX)
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
"IMPORTED_LOCATION" "${binary_dir}/lib/libgtest.a"
"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
set_target_properties(libgmock PROPERTIES
"IMPORTED_LOCATION" "${binary_dir}/lib/libgmock.a"
"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include")

file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(UnitTest ${SRCS})
# Link with other targets.
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC
                    ${CMAKE_SOURCE_DIR}/Modbuspp/lib/libModbuspp.a
                    libgtest
                    libgmock
                )

 set_target_properties(${PROJECT_NAME} PROPERTIES
                ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
            )


set(COVERAGE_EXCLUDES "./UnitTests/gtest/**")
INCLUDE( ${CMAKE_SOURCE_DIR}/cmake-module/CodeCoverage.cmake )

  append_coverage_compiler_flags()
  add_test(NAME UnitTest
  COMMAND UnitTest)
  message("Coverage is going to be generated")
  #set(COVERAGE_EXCLUDES
  #          'test/*'
  #          'extern/*'
  #          )
  #set(COVERAGE_LCOV_EXCLUDES
  #"/usr/include/*"
  #"/usr/include/c++/*"
  #"/usr/include/x86_64-linux-gnu/c++/7/bits/*"
  #)
  # SETUP_TARGET_FOR_COVERAGE_LCOV(NAME coverage
  #                          EXECUTABLE ${TEST_EXE_NAME}
  #                          )
#  setup_target_for_coverage_gcovr_xml(NAME coverage
#                                      EXECUTABLE UnitTest
#                                      EXCLUDE "**/c++/**" "gtest/*"
#                                      )




