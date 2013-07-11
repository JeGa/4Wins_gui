#ifndef IGAMEMANAGER_H
#define IGAMEMANAGER_H

#include "IGameController.h"
#include "IGame.h"

namespace controller
{
    
    class IGameManager
    {
    public:
        virtual ~IGameManager() {};
        
        virtual void newGame(data::IGame *game) = 0;
        virtual IGameController *getGameController() = 0;
        virtual bool input(int x, int y) = 0;
        virtual data::IGame *getGame() = 0; // From GameController
    };
    
}

#endif