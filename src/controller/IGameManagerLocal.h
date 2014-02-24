#ifndef IGAMEMANAGERLOCAL_H
#define IGAMEMANAGERLOCAL_H

#include "AGameManager.h"

namespace controller
{

    class IGameManagerLocal : public AGameManager
    {
    public:
        IGameManagerLocal(GameFactory *f) : AGameManager(f) {}
        virtual ~IGameManagerLocal() {}

        // adds the game to the manager and sets it to the active game
        virtual bool input(int x, int y) = 0;
        // Sets/gets game as active game for GameController
        virtual bool setActiveGame(int key) = 0;
        virtual int getActiveGame() = 0;
        virtual std::shared_ptr<data::IGame> getActiveGameRef() = 0;
    };
    
}

#endif