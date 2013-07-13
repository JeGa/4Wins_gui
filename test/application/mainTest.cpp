/* Defines boost test main */

/*
Be sure to use the newest MinGW compiler! 4.7!
============================================================================================================
 * How to build boost

bootstrap.bat

F:\ext\boost\tools\build\v2>
b2.exe install --prefix="F:\ext\boost_build" --toolset=gcc

F:\ext\boost>
F:\ext\boost_build\bin\b2.exe --build-dir="F:\ext\boost_build" toolset=gcc --build-type=complete stage
(--with-system ...)
(--show-libraries)

 * How to build fltk

download msys
download fltk tarball
./configure --prefix="..."
make
make install
cmakelists.txt edit

prefix mit '/'
 
  * How to set up code lite

Add Debug and Test build targets with correct executable file
add pre custom build command cd build;cmake -DCMAKE_BUILD_TYPE=Test ..
add tag include dirs
add plugin subst. code format

============================================================================================================

g++  -I ..\..\src\controller -I ..\..\src\data -I F:\ext\boost GameControllerTest.cpp GameFactoryTest.cpp ..\..\src\controller\GameControllerStandard.cpp ..\..\src\controller\GameControllerStrategy.cpp

g++ -I F:\ext\boost GameControllerTest.cpp GameFactoryTest.cpp -l lib4Wins_gui.a

============================================================================================================

==== How to compile and link a program with boost test ====

F:\jens_c++_projects\workspace\4Wins_gui\test\data>
g++ -I F:\ext\boost -I ..\..\src\data\ ..\..\src\data\impl\Cell.cpp CellTest.cpp -L F:\ext\boost\stage\lib -lboost_unit_test_framework-mgw46-d-1_53

-> Shared library link
To use static add the flag -static.

To auto-define the main function for boost test:
static:
	#define BOOST_TEST_MAIN
shared:
	#define BOOST_TEST_DYN_LINK
	#define BOOST_TEST_MODULE 4Wins_test
	
============================================================================================================
*/

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>