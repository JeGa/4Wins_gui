#include "GameManagerNetworkServer.h"
#include "TCPMessageUser.h"

namespace controller
{

    // TODO: Get factory as parameter
    GameManagerNetworkServer::GameManagerNetworkServer() :
        IGameManagerServer::IGameManagerServer(new GameFactory()),
        gc(factory->getGameController())
    {
        networkController.setExternalTCPConnectionObserver(this);
    }

    GameManagerNetworkServer::~GameManagerNetworkServer()
    {
        stop();
    }
    
    bool GameManagerNetworkServer::logoutPlayer(std::string name, std::string pw)
    {
        // Set logged-in to false
        return playerStatus(name, pw, false);
    }
    
    bool GameManagerNetworkServer::loginPlayer(std::string name, std::string pw)
    {
        // Set logged-in to true
        return playerStatus(name, pw, true);
    }
    
    int GameManagerNetworkServer::registerPlayer(std::string name, std::string pw)
    {
        return addPlayer(name, pw);
    }
    
    bool GameManagerNetworkServer::playerStatus(
        std::string name, std::string pw, bool playerStatus)
    {
        players[addPlayer(name, pw)]->setLoggedIn(playerStatus);
        return true; // TODO
    }
    
    void GameManagerNetworkServer::start()
    {
        networkController.startServer();
    }
    
    void GameManagerNetworkServer::stop()
    {
        networkController.stopServer();
    }
    
    std::vector<std::unique_ptr<TCPConnection>>&
        GameManagerNetworkServer::getConnections()
    {
        return networkController.getConnections();
    }
    
    // =========================================================================
    
    // Notified from the TCPConnection receive thread
    void GameManagerNetworkServer::notify(util::Subject *sub)
    {
        TCPConnection *con = static_cast<TCPConnection *>(sub);
        
        if (con->isActive()) {
            std::unique_ptr<TCPMessage> msg = con->getLastMessage();
            
            if (!msg)
                return;
            
            std::cout << msg->toString() << std::endl;
            
            // Check message type
            TCPMessageUser userMsg;
            
            // Is it a user message
            if (userMsg.createAck(msg->getFrameData())) {
                if (userMsg.isValid()) {
                    
                    if (userMsg.getQueryType() == QUERY_MSG_TYPE::REGISTER_QUERY) {
                        
                        if (registerPlayer(userMsg.getName(), userMsg.getPw()))
                            userMsg.setAck(true);
                        else
                            userMsg.setAck(false);
                            
                        con->sendMessage(userMsg);
                        
                    } else if (userMsg.getQueryType() == QUERY_MSG_TYPE::LOGIN_QUERY) {
                        
                        if (loginPlayer(userMsg.getName(), userMsg.getPw()))
                            userMsg.setAck(true);
                        else
                            userMsg.setAck(false);
                            
                        con->sendMessage(userMsg);
                        
                    } else if (userMsg.getQueryType() == QUERY_MSG_TYPE::LOGOUT_QUERY) {
                        
                        if (logoutPlayer(userMsg.getName(), userMsg.getPw()))
                            userMsg.setAck(true);
                        else
                            userMsg.setAck(false);
                            
                        con->sendMessage(userMsg);
                        
                    } else if (userMsg.getQueryType() == QUERY_MSG_TYPE::GET_PLAYERS_QUERY) {
                        
                        //userMsg.setAck(players);
                            
                        con->sendMessage(userMsg);
                        
                    }
                }
                
            }
        }
    }

}

