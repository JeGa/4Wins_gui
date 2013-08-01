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
    
    void GameManagerNetworkServer::start()
    {
        networkController.startServer();
    }
    
    void GameManagerNetworkServer::stop()
    {
        networkController.stopServer();
    }
    
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
                        
                    }
                }
            }
        }
        
    }
    
    std::vector<std::unique_ptr<TCPConnection>>&
        GameManagerNetworkServer::getConnections()
    {
        return networkController.getConnections();
    }
    
    bool GameManagerNetworkServer::loginPlayer(std::string name, std::string pw)
    {
        data::IPlayer *p = factory.getPlayer(name, pw);
        bool status = false;
        try {
            data::IPlayer *tmp = players.at(p->getKey());
            // Player in list
            
            tmp->setLoggedIn(true);
            
            status = true;
        } catch (std::out_of_range& e) {
            // Player not in list
        }
        
        delete p;
        return status;
    }
    
    bool GameManagerNetworkServer::registerPlayer(std::string name, std::string pw)
    {
        data::IPlayer *p = factory.getPlayer(name, pw);
        
        try {
            players.at(p->getKey());
            delete p;
            
            std::cout << "player already registered with " << p->getKey() << std::endl;
            
            return false;
        } catch (std::out_of_range& e) {
            
            players[p->getKey()] = p;
            
            std::cout << "Register player with " << p->getKey() << std::endl;
            
            return true;
        }
    }

}

