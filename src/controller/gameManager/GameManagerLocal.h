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
#include <map>

namespace controller
{

    class GameManagerLocal : public IGameManager
    {
    private:
        // The gc holds the active game and the 2 players
        IGameController *gc = nullptr;
        
        std::map<int, data::IGame *> games;
        std::map<int, data::IPlayer *> players;
        
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
        virtual IGameController *getGameController();
    };

}

#endif // GAMEMANAGERLOCAL_H
