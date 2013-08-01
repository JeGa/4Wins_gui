#include "GameManagerNetworkClient.h"

#include "TCPMessageUser.h"

namespace controller
{

    GameManagerNetworkClient::GameManagerNetworkClient()
    {
        networkController.setExternalTCPConnectionObserver(this);
    }

    GameManagerNetworkClient::~GameManagerNetworkClient()
    {
        if (networkController.isConnected())
            networkController.disconnect();
    }
    
    bool GameManagerNetworkClient::login()
    {
        if (waitingFor != QUERY_MSG_TYPE::NOT_SET)
            return false;
        
        if (!networkController.isConnected())
            networkController.connect();
     
        // Create message
        TCPMessageUser umsg;
        if (!umsg.createQuery(QUERY_MSG_TYPE::LOGIN_QUERY, *localPlayer))
            return false;
            
        // Login player: Send message
        handshake.lock();
        networkController.send(umsg);
        
        // Wait for ack
        waitingFor = QUERY_MSG_TYPE::LOGIN_QUERY;
        handshake.unlock();
        
        return true;
    }
    
    bool GameManagerNetworkClient::logout()
    {
        if (waitingFor != QUERY_MSG_TYPE::NOT_SET)
            return false;
        
        if (networkController.isConnected())
            networkController.disconnect();
            
        if (!localPlayer)
            return false;
        
        // Create message
        TCPMessageUser umsg;
        if (!umsg.createQuery(QUERY_MSG_TYPE::LOGOUT_QUERY, *localPlayer))
            return false;
            
        // Logout player: Send message
        handshake.lock();
        networkController.send(umsg);
        
        // Wait for ack
        waitingFor = QUERY_MSG_TYPE::LOGOUT_QUERY;
        handshake.unlock();
        
        return false;
    }
    
    bool GameManagerNetworkClient::registerUser(std::string name, std::string pw)
    {
        if (waitingFor != QUERY_MSG_TYPE::NOT_SET)
            return false;
            
        if (!networkController.isConnected())
            networkController.connect();
        
        // Create player 
        std::unique_ptr<data::IPlayer> p(factory.getPlayer(name, pw));
        localPlayer = std::move(p);
     
        // Create message
        TCPMessageUser umsg;
        if (!umsg.createQuery(QUERY_MSG_TYPE::REGISTER_QUERY, *localPlayer))
            return false;
            
        // Register player: Send message
        handshake.lock();
        networkController.send(umsg);
        
        // Wait for ack
        waitingFor = QUERY_MSG_TYPE::REGISTER_QUERY;
        handshake.unlock();
     
        return true;
    }
    
    bool GameManagerNetworkClient::ping()
    {
        return networkController.ping();
    }

    // Notified from the TCPConnection receive thread
    void GameManagerNetworkClient::notify(util::Subject *sub)
    {
        TCPConnection *con = static_cast<TCPConnection *>(sub);
        
        // Connection is closed:
        if (con->isActive()) {
            
            std::unique_ptr<TCPMessage> msg = con->getLastMessage();
            
            if (!msg)
                return;
            
            std::cout << msg->toString() << std::endl;
            
            // Check message
            TCPMessageUser umsg;
            
            handshake.lock();
            if (umsg.createUserMessage(msg->getFrameData())) {
                if (waitingFor == umsg.getQueryType()) {
                    if (waitingFor == QUERY_MSG_TYPE::REGISTER_QUERY) {
                        if (umsg.getAckStatus()) {
                            waitingFor = QUERY_MSG_TYPE::NOT_SET;
                        }
                    } else if (waitingFor == QUERY_MSG_TYPE::LOGIN_QUERY) {
                        if (umsg.getAckStatus()) {
                            localPlayer->setLoggedIn(true);
                            waitingFor = QUERY_MSG_TYPE::NOT_SET;
                        }
                    } else if (waitingFor == QUERY_MSG_TYPE::LOGOUT_QUERY) {
                        if (umsg.getAckStatus()) {
                            localPlayer->setLoggedIn(false);
                            waitingFor = QUERY_MSG_TYPE::NOT_SET;
                        }
                    }
                }
            }
            handshake.unlock();
        }
    }

}