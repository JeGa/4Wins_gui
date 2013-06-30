#ifndef GAMEFACTORYTEST_H
#define GAMEFACTORYTEST_H

#include <boost/test/unit_test.hpp>

#include "GameFactory.h"

namespace controller
{

    struct GameFactoryTest
    {
            GameFactory f;
            IField *field;

            GameFactoryTest()
            {
                field = f.getDefaultField();
            }

            ~GameFactoryTest()
            {
                delete field;
            }
    };

}

#endif // GAMEFACTORYTEST_H
