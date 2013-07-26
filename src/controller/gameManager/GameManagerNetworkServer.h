/*
* This class is used by multiple threads! To access the data synchronization
* mechanism must be used!
*
* Holds multiple game instances, the game controller holds one game
* that is played.
*/

#ifndef GAMEMANAGERNETWORKSERVER_H
#define GAMEMANAGERNETWORKSERVER_H

#include "IGameManager.h"
#include "IGame.h"
#include "IPlayer.h"
#include "IGameController.h"
#include <map>
#include "NetworkControllerServer.h"

namespace controller
{
    
    class GameManagerNetworkServer : public IGameManager
    {
    private:
        // The gc holds the active game and the 2 players
        // All clients use the same GameController.
        IGameController *gc = nullptr;
        NetworkControllerServer networkController;

        std::map<int, data::IGame *> games;
        std::map<int, data::IPlayer *> players;
    public:
        GameManagerNetworkServer(IGameController *gc);
        virtual ~GameManagerNetworkServer();
        
        virtual void newGame(data::IGame *game) {};
        virtual bool deleteGame(data::IGame *game) {return false;};
        virtual bool input(int x, int y) {return false;};
        virtual bool setActiveGame(data::IGame *game) {return false;};
        virtual data::IGame *getActiveGame() {return nullptr;};
    };

}

#endif // GAMEMANAGERNETWORKSERVER_H
