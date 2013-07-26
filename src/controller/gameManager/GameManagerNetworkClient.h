/*
* Theres no GameController for the client network manager.
* All calculations are made on the server.
* 
* The GameManager provides an abstraction to access the server
* through network.
*/

#ifndef GAMEMANAGERNETWORKCLIENT_H
#define GAMEMANAGERNETWORKCLIENT_H

#include "IGameManager.h"
#include <map>
#include "NetworkControllerClient.h"
#include "TCPMessage.h"

namespace controller
{

    class GameManagerNetworkClient : public IGameManager
    {
    private:
        data::IPlayer *localPlayer = nullptr; // The own player
    
        // This are copies from the server.
        std::map<int, data::IGame *> games;
        std::map<int, data::IPlayer *> players;
        
        NetworkControllerClient networkController;
        // If the game manager is waiting for a message from the server
        MSG_TYPE waitingFor = MSG_TYPE::UNDEF;
    
    public:
        GameManagerNetworkClient();
        virtual ~GameManagerNetworkClient();
        
        bool login(std::string name, std::string pw);
        bool logout(std::string name, std::string pw);
        bool registerUser(std::string name, std::string pw);
        virtual void newGame(data::IGame *game) {};
        virtual bool deleteGame(data::IGame *game) {return false;};
        virtual bool input(int x, int y) {return false;};
        
        // Do not need that: ??
        virtual bool setActiveGame(data::IGame *game) {return false;};
        virtual data::IGame *getActiveGame() {return nullptr;};
        

    };

}

#endif // GAMEMANAGERNETWORKCLIENT_H
