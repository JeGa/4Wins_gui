/*
* The GameManager is resonsible for the memory management.
* One GameController is used for all games.
*/

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
        virtual bool deleteGame(data::IGame *game) = 0;
        virtual bool input(int x, int y) = 0;
        virtual bool setActiveGame(data::IGame *game) = 0;
        virtual data::IGame *getActiveGame() = 0; // From GameController
//        virtual std::map<data::IGame *> getGames() = 0;
//        virtual std::map<data::IPlayer *> getPlayers() = 0;
    };
    
}

#endif