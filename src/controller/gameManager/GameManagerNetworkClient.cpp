#include "GameManagerNetworkClient.h"

namespace controller
{

    GameManagerNetworkClient::GameManagerNetworkClient()
    {
    }

    GameManagerNetworkClient::~GameManagerNetworkClient()
    {
    }
    
    bool GameManagerNetworkClient::login(std::string name, std::string pw)
    {
        networkController.connect();
        
        // Create login query message
        
        //networkController.sendMessage(msg);
        
        networkController.disconnect(); // If no successful login
        
        return true;
    }
    
    bool GameManagerNetworkClient::logout(std::string name, std::string pw)
    {
        
        networkController.disconnect();
        
        return false;
    }
    
    bool GameManagerNetworkClient::registerUser(std::string name, std::string pw)
    {
        // Create player 
        networkController.connect();
     
        // Create message
     
        // Register player: Send message
     
        return false;
    }
    
    // Notified when received thread got a message
//    void GameManagerNetworkClient::notify()
//    {
//        getReceivedMessage();
//        
//        
//    }

}