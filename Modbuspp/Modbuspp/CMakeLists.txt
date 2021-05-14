
project(Modbuspp LANGUAGES C CXX)


########Source Files#############
set(Sources__Configuration_Layer
    "src/config.cpp"
)
set(Sources__TCPManagement_Layer
    "src/tcp.cpp"
)
set(Sources__Comm_Layer
    "src/comm.cpp"
)
set(Sources
    "src/main.cpp"
)
source_group("src/CommLayer" FILES ${Sources__Comm_Layer})
source_group("src/TCPManagementLayer" FILES ${Sources__TCPManagement_Layer})
source_group("src/ConfigLayer" FILES ${Sources__Configuration_Layer})
source_group("src" FILES ${Sources})


########## Headers ############################
set(Headers__Config_Layer
    "inc/config.h"
)
set(Headers__TCPManagement_Layer
    "inc/tcpip_interface.h"
)
set(Headers__Comm_Layer
    "inc/comm.h"
)

source_group("inc/ConfigLayer" FILES ${Headers__Config_Layer})
source_group("inc/TCPManagementLayer" FILES ${Headers__TCPManagement_Layer})
source_group("inc/CommLayer" FILES ${Headers__Comm_Layer})




########Port Includes#####################
set(Headers__Port_Layer
"port/posix/tcpip_posix.h"
)

set(Sources__Port_Layer
 "port/posix/tcpip_posix.cpp"
)

if (CMAKE_PLATFORM STREQUAL "POSIX")

    #list(APPEND Headers__Port_Layer "port/posix/tcpip_posix.h")
    #list(APPEND Sources__Port_Layer "port/posix/tcpip_posix.cpp")
endif()

source_group("port/inc" FILES ${Headers__Port_Layer})
source_group("port/src" FILES ${Sources__Port_Layer})


########All Files#############
set(ALL_FILES
     ${Sources__Comm_Layer}
     ${Sources__Configuration_Layer}
     ${Sources__TCPManagement_Layer}
     ${Sources__Port_Layer}
     ${Sources}
     ${Headers__Config_Layer}
     ${Headers__TCPManagement_Layer}
     ${Headers__Comm_Layer}
     ${Headers__Port_Layer}
 )

include_directories("${CMAKE_SOURCE_DIR}/Modbuspp/port/posix")
include_directories("${CMAKE_SOURCE_DIR}/Modbuspp/inc")
message(STATUS "Generating project is done!")

set(TARGET_BINARY ${PROJECT_NAME})

INCLUDE( ${CMAKE_SOURCE_DIR}/cmake-module/CodeCoverage.cmake )

  append_coverage_compiler_flags()

#Custom target for build and debug with GDB
#add_custom_target(build_and_debug ALL DEPENDS ${TARGET_BINARY})
#add_custom_command(TARGET build_and_debug POST_BUILD
#    COMMAND echo "Hello World1"

#)
if (STATIC_LIB STREQUAL "ON")
# Declare the library
add_library(${PROJECT_NAME} STATIC
    ${ALL_FILES}
)
else()
add_executable(${PROJECT_NAME} ${ALL_FILES})
endif()


#Output Directory

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

################################################################################
# Include directories
################################################################################
include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
    "${CMAKE_CURRENT_SOURCE_DIR}/port"
     "${CMAKE_CURRENT_SOURCE_DIR}/port/posix"
)

message(STATUS "Cmake Current Source dir: ${CMAKE_CURRENT_SOURCE_DIR}")

