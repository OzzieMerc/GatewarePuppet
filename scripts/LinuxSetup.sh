#! /bin/bash

#########################################################################
# File: LinuxSetup.sh
# Author: Ozzie Mercado
# Created: November 25, 2020
# Description: Creates a folder for the project on Linux and runs CMake.
#   Two projects are created, one for debug builds and one for release.
#########################################################################

cd ../

# Make build folder if needed.
[ ! -d "build" ] && mkdir build
cd build


# Make debug folder if needed.
[ ! -d "debug" ] && mkdir debug
cd debug

# Run CMake to create debug version.
cmake ../../ -G "CodeLite - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug;

cd ../


# Make release folder if needed.
[ ! -d "release" ] && mkdir release
cd release

# Run CMake to create release version.
cmake ../../ -G "CodeLite - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release;

cd ../
