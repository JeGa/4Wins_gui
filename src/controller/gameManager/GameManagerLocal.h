/*
* Is responsible for the memory-management of players, game,
* and game controller.
*/

#ifndef GAMEMANAGERLOCAL_H
#define GAMEMANAGERLOCAL_H

#include "IGameManagerLocal.h" // Base class: controller::IGameManager
#include "IPlayer.h"
#include "IGame.h"
#include "IGameController.h"
#include <map>

namespace controller
{

    class GameManagerLocal : public IGameManagerLocal
    {
    private:
        // The gc holds the active game and the 2 players
        // With the local version, there is only one GameManager,
        // so it needs a GameController to play a game.
        IGameController *gc = nullptr;
        
        void clear();
        void addPlayer(data::IPlayer *player);
    public:
        GameManagerLocal(IGameController *gc);
        virtual ~GameManagerLocal();
        
        // Game has to contain 2 players, adds the game to the manager
        // and sets it to the active game
        virtual void newGame(data::IGame *game);
        virtual bool deleteGame(data::IGame *game);
        virtual bool input(int x, int y); // For active game
        virtual bool setActiveGame(data::IGame *game);
        virtual data::IGame *getActiveGame();
    };

}

#endif // GAMEMANAGERLOCAL_H
