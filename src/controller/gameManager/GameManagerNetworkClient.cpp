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
    
    bool GameManagerNetworkClient::login(std::string name, std::string pw)
    {
        if (waitingFor != QUERY_MSG_TYPE::NOT_SET)
            return false;
        
        if (!networkController.isConnected())
            networkController.connect();
        
        boost::unique_lock<boost::mutex> l(handshake);
        
        // Already logged in
        if (localPlayer)
            return false;
            
        // Create player 
        std::unique_ptr<data::IPlayer> p(factory.getPlayer(name, pw));
        localPlayer = std::move(p);
     
        // Create message
        TCPMessageUser umsg;
        if (!umsg.createQuery(QUERY_MSG_TYPE::LOGIN_QUERY, *localPlayer))
            return false;
            
        // Login player: Send message
        networkController.send(umsg);
        
        // Wait for ack
        waitingFor = QUERY_MSG_TYPE::LOGIN_QUERY;
        
        return true;
    }
    
    bool GameManagerNetworkClient::logout()
    {
        if (waitingFor != QUERY_MSG_TYPE::NOT_SET)
            return false;
            
        // Should normally be connected
        if (!networkController.isConnected())
            networkController.connect();
            
        boost::unique_lock<boost::mutex> l(handshake);
        
        if (!localPlayer)
            return false;
        
        // Create message
        TCPMessageUser umsg;
        if (!umsg.createQuery(QUERY_MSG_TYPE::LOGOUT_QUERY, *localPlayer))
            return false;
            
        // Logout player: Send message
        networkController.send(umsg);
        
        // Wait for ack
        waitingFor = QUERY_MSG_TYPE::LOGOUT_QUERY;
        
        return true;
    }
    
    bool GameManagerNetworkClient::registerUser(std::string name, std::string pw)
    {
        if (waitingFor != QUERY_MSG_TYPE::NOT_SET)
            return false;
            
        if (!networkController.isConnected())
            networkController.connect();
        
        // Create player (only local variable)
        std::unique_ptr<data::IPlayer> p(factory.getPlayer(name, pw));
     
        // Create message
        TCPMessageUser umsg;
        if (!umsg.createQuery(QUERY_MSG_TYPE::REGISTER_QUERY, *p))
            return false;
            
        // Register player: Send message
        boost::unique_lock<boost::mutex> l(handshake);
        
        networkController.send(umsg);
        
        // Wait for ack
        waitingFor = QUERY_MSG_TYPE::REGISTER_QUERY;
     
        return true;
    }
    
    bool GameManagerNetworkClient::ping()
    {
        if (networkController.isConnected())
            return true;
        return networkController.ping();
    }
    
    bool GameManagerNetworkClient::isLoggedIn()
    {
        if (localPlayer)
            return true;
        return false;
    }
    
    bool GameManagerNetworkClient::getData()
    {
        if (waitingFor != QUERY_MSG_TYPE::NOT_SET)
            return false;
            
        // Should normally be connected
        if (!networkController.isConnected())
            networkController.connect();
            
        boost::unique_lock<boost::mutex> l(handshake);
        
        if (!localPlayer)
            return false;
        
        // Create message
        TCPMessageUser umsg;
        if (!umsg.createQuery(QUERY_MSG_TYPE::GET_PLAYERS_QUERY, *localPlayer))
            return false;
            
        // Logout player: Send message
        networkController.send(umsg);
        
        // Wait for ack
        waitingFor = QUERY_MSG_TYPE::GET_PLAYERS_QUERY;
        
        return true;
    }
    
    // =========================================================================

    // Notified from the TCPConnection receive thread
    void GameManagerNetworkClient::notify(util::Subject *sub)
    {
        TCPConnection *con = static_cast<TCPConnection *>(sub);
        
        if (con->isActive()) {
            
            std::unique_ptr<TCPMessage> msg = con->getLastMessage();
            if (!msg)
                return; // Message was already handled
            
            std::cout << msg->toString() << std::endl;
            
            // Check message
            TCPMessageUser umsg;
            
            boost::unique_lock<boost::mutex> l(handshake);
            
            // When the manager is waiting for this message
            
            // User message
            if (umsg.createUserMessage(msg->getFrameData())) {
                
                if (waitingFor == umsg.getQueryType()) {
                    
                    if (waitingFor == QUERY_MSG_TYPE::REGISTER_QUERY) {
                        if (umsg.getAckStatus()) {
                        
                        }
                        
                    } else if (waitingFor == QUERY_MSG_TYPE::LOGIN_QUERY) {
                        if (umsg.getAckStatus()) {
                            if (localPlayer)
                                localPlayer->setLoggedIn(true);
                        } else
                            localPlayer.release();
                        
                    } else if (waitingFor == QUERY_MSG_TYPE::LOGOUT_QUERY) {
                        if (umsg.getAckStatus()) {
                            if (localPlayer) {
                                clearPlayers();
                                localPlayer.release();
                            }
                        }
                        
                    } else if (waitingFor == QUERY_MSG_TYPE::GET_PLAYERS_QUERY) {
                        if (umsg.getAckStatus()) {
                            players = umsg.getPlayers();
                        }
                    }
                    
                    waitingFor = QUERY_MSG_TYPE::NOT_SET;
                }
            }
        }
    }

}