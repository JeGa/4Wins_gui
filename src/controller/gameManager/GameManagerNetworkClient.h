/*
* There is no GameController for the client network manager.
* All calculations are made by the server.
* 
* The GameManager provides an abstraction to access the server
* through network.
*/

#ifndef GAMEMANAGERNETWORKCLIENT_H
#define GAMEMANAGERNETWORKCLIENT_H

#include "IGameManagerClient.h"
#include "NetworkControllerClient.h"
#include "TCPMessage.h"
#include "Observer.h"
#include "GameFactory.h"
#include "TCPMessageUser.h"
#include <boost/thread.hpp>
#include <map>

namespace controller
{

    class GameManagerNetworkClient :
        public IGameManagerClient,
        public util::Observer
    {
    private:
        // Contains only a reference if the player is logged in or
        // tries to log in.
        std::shared_ptr<data::IPlayer> localPlayer;
        NetworkControllerClient networkController;

        std::map<int, std::unique_ptr<TCPMessage>> messageQueue;
        
        boost::mutex handshake;

        void handleUserMessage(TCPMessageUser& umsg);
        bool isWaitingFor(int key);
        bool tryConnect();
    public:
        GameManagerNetworkClient();
        virtual ~GameManagerNetworkClient();
        
        virtual bool login(std::string name, std::string pw);
        virtual bool logout();
        virtual bool registerUser(std::string name, std::string pw);

        virtual bool ping();
        virtual bool isLoggedIn();
        virtual bool getData();

        virtual std::shared_ptr<data::IPlayer> getLocalPlayerRef();

        // TODO:
        virtual void newGame(data::IGame *game) {};
        virtual bool deleteGame(data::IGame *game) {return false;};
        virtual bool input(int x, int y) {return false;};
        
        virtual void notify(util::Subject* sub);
    };

}

#endif // GAMEMANAGERNETWORKCLIENT_H