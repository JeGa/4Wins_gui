/*
* Is responsible for the memory-management of players, game,
* and game controller.
*/

#ifndef GAMEMANAGERLOCAL_H
#define GAMEMANAGERLOCAL_H

#include "IGameManager.h" // Base class: controller::IGameManager
#include "IPlayer.h"
#include "IGame.h"
#include "IGameController.h"

namespace controller
{

    class GameManagerLocal : public IGameManager
    {
    private:
        IGameController *gc = nullptr;
        
        void clear();
    public:
        GameManagerLocal(IGameController *gc);
        virtual ~GameManagerLocal();
        
        virtual void newGame(data::IGame *game);
        virtual IGameController *getGameController();
        virtual bool input(int x, int y);
    };

}

#endif // GAMEMANAGERLOCAL_H
