/*
* The GameManager is resonsible for the memory management.
* One GameController is used for all games.
*/

#ifndef IGAMEMANAGERLOCAL_H
#define IGAMEMANAGERLOCAL_H

#include "IGameController.h"
#include "IGame.h"
#include "AGameManager.h"

namespace controller
{
    
    class IGameManagerLocal : public AGameManager
    {
    public:
        IGameManagerLocal() : AGameManager(GameFactory& f) {}
        virtual ~IGameManagerLocal() {};

        virtual bool newGame(std::string p1, std::string p2) = 0;
//        virtual bool deleteGame(data::IGame *game) = 0;
        virtual bool input(int x, int y) = 0;
        virtual bool setActiveGame(data::IGame *game) = 0;
        virtual data::IGame *getActiveGame() = 0; // From GameController







        virtual void newGame(data::IGame *game) = 0;
        virtual bool deleteGame(data::IGame *game) = 0;
        virtual bool input(int x, int y) = 0;
        virtual bool setActiveGame(data::IGame *game) = 0;
        virtual data::IGame *getActiveGame() = 0; // From GameController
    };
    
}

#endif