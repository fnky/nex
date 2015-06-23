cmake_minimum_required (VERSION 2.6)
project (nex)

message ("setting up the nex game engine\n")

# Setup some general cmake settings
set (CMAKE_COLOR_MAKEFILE ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS 1)

set (BUILD_SHARED_LIBS false)

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

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Setup some base path variables.
set (NEX_EXTLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extlib)
set (NEX_STB_IMAGE_INCLUDE ${NEX_EXTLIB_DIR}/stb_image)
set (NEX_FREETYPE_INCLUDE ${NEX_EXTLIB_DIR}/freetype/include)

# Include external library headers.
set (NEX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (NEX_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set (NEX_SYSTEM_LIB nex-system)
set (NEX_FILESYSTEM_LIB nex-filesystem)
set (NEX_MATH_LIB nex-math)
set (NEX_WINDOW_LIB nex-window)
set (NEX_GAME_LIB nex-game)
set (NEX_GFX_LIB nex-gfx)

# Add the external library builds.

add_subdirectory (${NEX_EXTLIB_DIR}/freetype)

# Add our library folder.
add_subdirectory (src/nex)

# Enable this to build the nex test project.
add_subdirectory (src/testing)
