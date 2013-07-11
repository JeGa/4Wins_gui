/* Defines boost test main */

/*
 * How to build boost

F:\ext\boost\tools\build\v2>
b2.exe install --prefix="F:\ext\boost_build" --toolset=gcc

F:\ext\boost>
F:\ext\boost_build\bin\b2.exe --build-dir="F:\ext\boost_build" toolset=gcc --build-type=complete stage

 * How to build fltk

download msys
download fltk tarball
./configure --prefix="..."
make
make install
cmakelists.txt edit
 
  * How to set up code lite

Add Debug and Test build targets with correct executable file
add pre custom build command cd build;cmake -DCMAKE_BUILD_TYPE=Test ..
add tag include dirs
add plugin subst. code format

*/

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>