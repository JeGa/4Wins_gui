#ifndef PLAYERTEST_H
#define PLAYERTEST_H

#include <boost/test/unit_test.hpp>

#include "impl/Player.h"

namespace data
{

    struct PlayerTest
    {
            Player p1;

            PlayerTest() : p1("Han Solo", "Falcon") {}
            ~PlayerTest() {}
    };

}

#endif // PLAYERTEST_H
