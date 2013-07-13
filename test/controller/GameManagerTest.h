#ifndef GAMEMANAGERTEST_H
#define GAMEMANAGERTEST_H

#include <boost/test/unit_test.hpp>

#include "GameControllerStrategy.h"
#include "GameControllerStandard.h"
#include "GameManagerLocal.h"
#include "Player.h"
#include "Game.h"
#include "GameFactory.h"

namespace controller
{

    struct GameManagerTest
    {
        
        GameManagerLocal *manager;
        
        GameControllerStrategy *gc;
        IGame *game;
        IPlayer *p1;
        IPlayer *p2;
            
        GameFactory f;
        
    
        GameManagerTest()
        {
            gc = f.getGameController();
            
            p1 = f.getPlayer("p1", "p1");
            p2 = f.getPlayer("p2", "p2");
            game = f.getGameDefault(p1, p2, p1);
            
            manager = new GameManagerLocal(gc);
            manager->newGame(game);
        };
        
        ~GameManagerTest()
        {
            delete manager;
        };

    };

}

#endif // GAMEMANAGERTEST_H
