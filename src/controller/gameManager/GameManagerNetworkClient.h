/*
* Theres no GameController for the client network manager.
* All calculations are made on the server.
* 
* The GameManager provides an abstraction to access the server
* through network.
*/

#ifndef GAMEMANAGERNETWORKCLIENT_H
#define GAMEMANAGERNETWORKCLIENT_H

#include "IGameManagerClient.h"
#include <map>
#include "NetworkControllerClient.h"
#include "TCPMessage.h"
#include "Observer.h"
#include "GameFactory.h"
#include <boost/thread.hpp>

namespace controller
{

    class GameManagerNetworkClient :
        public IGameManagerClient,
        public util::Observer
    {
    private:
        std::unique_ptr<data::IPlayer> localPlayer; // The own player
        
        NetworkControllerClient networkController;
        GameFactory factory;
        
        // If the game manager is waiting for a message from the server
        QUERY_MSG_TYPE waitingFor = QUERY_MSG_TYPE::NOT_SET;
        
        boost::mutex handshake;
        
    public:
        GameManagerNetworkClient();
        virtual ~GameManagerNetworkClient();
        
        virtual bool login(std::string name, std::string pw);
        virtual bool logout();
        virtual bool registerUser(std::string name, std::string pw);
        virtual bool ping();
        virtual bool getData();
        
        virtual bool isLoggedIn();
        
        virtual void newGame(data::IGame *game) {};
        virtual bool deleteGame(data::IGame *game) {return false;};
        virtual bool input(int x, int y) {return false;};
        
        virtual void notify(util::Subject * sub);
    };

}

#endif // GAMEMANAGERNETWORKCLIENT_H
