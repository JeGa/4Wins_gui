#ifndef GAMETEST_H
#define GAMETEST_H

#include <boost/test/unit_test.hpp>

#include "impl/Game.h"
#include "impl/Player.h"
#include "IPlayer.h"
#include "GameFactory.h"

namespace data
{

    struct GameTest
    {
            IPlayer *p1;
            IPlayer *p2;
            Game *game;
            controller::GameFactory f;

            GameTest()
            {
                p1 = new Player("Luke Skywalker", "R2D2");
                p2 = new Player("Darth Vader", "ATAT");

                game = new Game(f.getDefaultField(), p1, p2, p1);
            }

            ~GameTest()
            {
                delete p1;
                delete p2;
                delete game;
            }
    };

}

#endif // GAMETEST_H
