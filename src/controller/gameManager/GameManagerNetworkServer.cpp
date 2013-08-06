#include "GameManagerNetworkServer.h"
#include "TCPMessageUser.h"

namespace controller
{

    GameManagerNetworkServer::GameManagerNetworkServer(IGameController *gc)
        : gc(gc)
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
    
    bool GameManagerNetworkServer::registerPlayer(std::string name, std::string pw)
    {
        data::IPlayer *p = factory.getPlayer(name, pw);
        
        try {
            players.at(p->getKey());
            delete p;
            
            return false;
        } catch (std::out_of_range& e) {
            
            players[p->getKey()] = p;
            
            return true;
        }
    }
    
    bool GameManagerNetworkServer::playerStatus(
        std::string name, std::string pw, bool playerStatus)
    {
        data::IPlayer *p = factory.getPlayer(name, pw);
        bool status = false;
        
        try {
            data::IPlayer *tmp = players.at(p->getKey());
            // Player in list
            
            tmp->setLoggedIn(playerStatus);
            
            status = true;
        } catch (std::out_of_range& e) {
            // Player not in list
        }
        
        delete p;
        return status;
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
                        
                        userMsg.setAck(players);
                            
                        con->sendMessage(userMsg);
                        
                    }
                }
                
            }
        }
    }

}

