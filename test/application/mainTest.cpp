/* Defines boost test main */
/*
F:\ext\boost\tools\build\v2>
b2.exe install --prefix="F:\ext\boost_build" --toolset=gcc

F:\ext\boost>
F:\ext\boost_build\bin\b2.exe --build-dir="F:\ext\boost_build" tool set=gcc --build-type=complete stage*/

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>