#ifndef IGAMEMANAGER_H
#define IGAMEMANAGER_H

#include "IGameController.h"

namespace controller
{
    
    class IGameManager
    {
    public:
        virtual ~IGameManager() {};
        
        virtual void newGame(data::IGame *game) = 0;
        virtual IGameController *getGameController() = 0;
        virtual bool input(int x, int y) = 0;
    };
    
}

#endif