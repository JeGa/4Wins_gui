/*
* This class is used by multiple threads! To access the data
* synchronization mechanism must be used!
*
* The game controller holds one game that is played.
*/

#ifndef GAMEMANAGERNETWORKSERVER_H
#define GAMEMANAGERNETWORKSERVER_H

#include "IGameManagerServer.h"
#include "IGame.h"
#include "IPlayer.h"
#include "IGameController.h"
#include "NetworkControllerServer.h"
#include "Observer.h"
#include "GameFactory.h"
#include "TCPConnection.h"
#include "TCPMessageUser.h"
#include <map>
#include <memory>

namespace controller
{
    
    class GameManagerNetworkServer :
        public IGameManagerServer,
        public util::Observer
    {
    private:
        // The gc holds the active game and the 2 players
        // All clients use the same GameController.
        std::unique_ptr<IGameController> gc;
        NetworkControllerServer networkController;
        
        void loginPlayer(std::string name, std::string pw);
        void logoutPlayer(std::string name, std::string pw);
        void playerStatus(std::string name, std::string pw, bool playerStatus);
        void handleUserMessage(TCPConnection *con, TCPMessageUser& umsg);
    public:
        GameManagerNetworkServer();
        virtual ~GameManagerNetworkServer();
        
        void start();
        void stop();

        // TODO:
        virtual void newGame(data::IGame *game) {};
        virtual bool deleteGame(data::IGame *game) {return false;};
        virtual bool input(int x, int y) {return false;};
        virtual bool setActiveGame(data::IGame *game) {return false;};
        virtual data::IGame *getActiveGame() {return nullptr;};
        
        std::vector<std::unique_ptr<TCPConnection>>& getConnections();
        
        virtual void notify(util::Subject * sub);
    };

}

#endif // GAMEMANAGERNETWORKSERVER_H
