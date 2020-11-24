:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: File: CMakeLists.txt
:: Author: Ozzie Mercado
:: Created: November 24, 2020
:: Description: Creates a folder for the project and runs CMake.
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

@echo off

cd ../

:: Make build folder if needed.
if not exist "build" mkdir build
cd build

:: Make VisualStudio folder if needed.
if not exist "VisualStudio" mkdir VisualStudio
cd VisualStudio

:: Run CMake.
cmake -A x64 "../../"

:: Pause so any important information (such as errors) can be read.
pause