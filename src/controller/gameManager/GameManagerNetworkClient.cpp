#include "GameManagerNetworkClient.h"

#include "TCPMessageUser.h"

namespace controller
{

    // TODO: Get factory as parameter
    GameManagerNetworkClient::GameManagerNetworkClient() :
        IGameManagerClient::IGameManagerClient(new GameFactory())
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

        if (!networkController.isConnected())
            return false;

        boost::unique_lock<boost::mutex> l(handshake);

        // Already logged in or already trying to log in.
        if (localPlayer)
            return false;

        // TODO: Could use unique ptr ...
        localPlayer = std::shared_ptr<data::IPlayer>(
                          factory->getPlayer(name, pw));

        TCPMessageUser umsg;
        if (!umsg.createQuery(QUERY_MSG_TYPE::LOGIN_QUERY, *localPlayer))
            return false;

        networkController.send(umsg);
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

        if (!networkController.isConnected())
            return false;

        boost::unique_lock<boost::mutex> l(handshake);

        // If not logged in or not trying to log in.
        if (!localPlayer)
            return false;

        TCPMessageUser umsg;
        if (!umsg.createQuery(QUERY_MSG_TYPE::LOGOUT_QUERY, *localPlayer))
            return false;

        networkController.send(umsg);
        waitingFor = QUERY_MSG_TYPE::LOGOUT_QUERY;

        return true;
    }

    bool GameManagerNetworkClient::registerUser(std::string name, std::string pw)
    {
        if (waitingFor != QUERY_MSG_TYPE::NOT_SET)
            return false;

        if (!networkController.isConnected())
            networkController.connect();

        if (!networkController.isConnected())
            return false;

        // Create player (only local variable)
        std::shared_ptr<data::IPlayer> p(factory->getPlayer(name, pw));

        TCPMessageUser umsg;
        if (!umsg.createQuery(QUERY_MSG_TYPE::REGISTER_QUERY, *p))
            return false;

        boost::unique_lock<boost::mutex> l(handshake);

        networkController.send(umsg);
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
        boost::unique_lock<boost::mutex> l(handshake);
        if (localPlayer)
            return localPlayer->isLoggedIn();
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

    std::shared_ptr<data::IPlayer> GameManagerNetworkClient::getLocalPlayerRef()
    {
        return localPlayer;
    }

    // =========================================================================

    // Notified from the TCPConnection receive thread
    void GameManagerNetworkClient::notify(util::Subject *sub)
    {
        TCPConnection *con = dynamic_cast<TCPConnection *>(sub);

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
                if (umsg.isValid()) {
                    if (waitingFor == umsg.getQueryType()) {
                        handleUserMessage(umsg);
                    }
                }
            }
        }
    }

    void GameManagerNetworkClient::handleUserMessage(TCPMessageUser& umsg)
    {
        if (waitingFor == QUERY_MSG_TYPE::REGISTER_QUERY) {
            if (umsg.getAckStatus()) {
                // TODO: How to notify?
            }
        } else if (waitingFor == QUERY_MSG_TYPE::LOGIN_QUERY) {
            if (umsg.getAckStatus()) {
                if (localPlayer)
                    localPlayer->setLoggedIn(true);
            } else
                localPlayer.reset();
        } else if (waitingFor == QUERY_MSG_TYPE::LOGOUT_QUERY) {
            if (umsg.getAckStatus()) {
                if (localPlayer)
                    localPlayer.reset();
            }
        } else if (waitingFor == QUERY_MSG_TYPE::GET_PLAYERS_QUERY) {
            if (umsg.getAckStatus()) {
                clearPlayers();
                //clearGames();
                //players = umsg.getPlayers();
                //games = umsg.getGames();
            }
        }

        waitingFor = QUERY_MSG_TYPE::NOT_SET;
    }

}
