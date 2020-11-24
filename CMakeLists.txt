#########################################################################################
# File: CMakeLists.txt
# Author: Ozzie Mercado
# Created: November 24, 2020
# Description: Generates the project on Windows. Tested for use with Visual Studio 2019.
#########################################################################################

cmake_minimum_required(VERSION 3.10)

project(GatewarePuppet)

# Gateware uses unicode on some of its libraries.
ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

# Recursively create a list of .h/.cpp files in the project folder.
file(
	GLOB_RECURSE ProjectFiles
    ./project/*.h
    ./project/*.cpp
)

# Set up the project on the appropriate platform.
if (WIN32)
    add_executable (GatewarePuppet ${ProjectFiles})
elseif(APPLE)
    message("ERROR: Mac is not supported due to a rendering issue with Gateware.\n")
elseif (UNIX AND NOT APPLE)
    # Linux support for this project is untested.
endif()

# Preserves the folder structure.
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${ProjectFiles})