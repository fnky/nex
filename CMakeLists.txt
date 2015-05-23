cmake_minimum_required (VERSION 2.6)
project (nex)

message ("setting up the nex game engine")

# Setup some general cmake settings
set (CMAKE_COLOR_MAKEFILE ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Set the default build if none was set already.
if (NOT DEFINED CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Debug)
endif ()

# Detect the current platform and add the correct definitions.
if (WIN32)
    set (NEX_OS win32)
    add_definitions (-DNEX_OS_WIN32)
elseif (UNIX)
    set (NEX_OS unix)
    add_definitions (-DNEX_OS_UNIX)
elseif (APPLE)
    error ("apple os is currently unsupported!")
    set (NEX_OS apple)
    add_definitions (-DNEX_OS_APPLE)
endif (WIN32)

message ("detected os: " ${NEX_OS})

# Enable C++11
if (APPLE)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -stdlib=libc++")
elseif (UNIX)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")
elseif (WIN32)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")
endif(APPLE)

# Build static stdlibs on GCC and MingW
if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
endif()

# Setup some base path variables.
set (NEX_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set (NEX_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)


# Setup some include path varibles for people only using a select few systems.
set (NEX_MATH_INCLUDE ${NEX_INCLUDE_DIR}/nex/math)
set (NEX_SYSTEM_INCLUDE ${NEX_INCLUDE_DIR}/nex/system)

set (NEX_MATH_LIB nex-math)
set (NEX_SYSTEM_LIB nex-systen)

add_subdirectory (src/nex)
add_subdirectory (src/testing)
