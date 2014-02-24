#ifndef GAMEMANAGERLOCAL_H
#define GAMEMANAGERLOCAL_H

#include "IGameManagerLocal.h"
#include "IPlayer.h"
#include "IGame.h"
#include "IGameController.h"

namespace controller
{

    class GameManagerLocal : public IGameManagerLocal
    {
    private:
        // The gc holds the active game and the 2 players.
        // With the local version, there is only one GameManager,
        // so it needs a GameController to play a game.
        std::unique_ptr<IGameController> gc;
    public:
        GameManagerLocal();
        virtual ~GameManagerLocal() {}
        
        virtual bool input(int x, int y);
        virtual bool setActiveGame(int key);
        virtual int getActiveGame();
        virtual std::shared_ptr<data::IGame> getActiveGameRef();
    };

}

#endif // GAMEMANAGERLOCAL_H
