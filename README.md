4Wins_gui
=========

The 4Wins_basic with a gui and a few new functions.

# Introduction
The 4Wins_gui project is developed under a different environment and with different
tools as the 4Wins_basic project:

* OS is Windows 7
* IDE is CodeLite
* CMake is used as buildtool
* Boost test is used for unit tests

# How to install
Set the required variables at the top of the CMakeLists.txt file.

You need the FLTK libraries to run CMake.

To run the unit tests you need to install boost test and set the CMake Variable
CMAKE_BUILD_TYPE to "Test".

Running CMake:
* Download and install CMake
* Create directory for binaries
* "cd" to this directory
* cmake <Dir. where CMakeLists.txt is> (Flag used to set your compiler)
* Compile it with your compiler (MSVS, Makefile, ...)

When I am ready, I upload binaries for Windows ... .
