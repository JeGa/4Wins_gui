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
        networkController.connect();
        return true;

        if (!networkController.isConnected())
            networkController.connect();

        if (!networkController.isConnected())
            return false;

        boost::unique_lock<boost::mutex> l(handshake);

        // Already logged in or already trying to log in.
        if (localPlayer)
            return false;

        localPlayer = std::shared_ptr<data::IPlayer>(
                          factory->getPlayer(name, pw));

        std::unique_ptr<TCPMessageUser> umsg(new TCPMessageUser);
        if (!umsg->createQueryMessage(QUERY_MSG_TYPE_USER::LOGIN_QUERY, localPlayer))
            return false;

        networkController.send(*umsg);

        messageQueue[umsg->getMsgKey()] = std::move(umsg);
        return true;
    }

    bool GameManagerNetworkClient::logout()
    {
        networkController.disconnect();
        return true;

        // Should normally be connected
        if (!networkController.isConnected())
            networkController.connect();

        if (!networkController.isConnected())
            return false;

        boost::unique_lock<boost::mutex> l(handshake);

        // If not logged in or not trying to log in.
        if (!localPlayer)
            return false;

        std::unique_ptr<TCPMessageUser> umsg(new TCPMessageUser);
        if (!umsg->createQueryMessage(QUERY_MSG_TYPE_USER::LOGOUT_QUERY, localPlayer))
            return false;

        networkController.send(*umsg);

        messageQueue[umsg->getMsgKey()] = std::move(umsg);
        return true;
    }

    bool GameManagerNetworkClient::registerUser(std::string name, std::string pw)
    {
        if (!networkController.isConnected())
            networkController.connect();

        if (!networkController.isConnected())
            return false;

        // Create player (only local variable)
        std::shared_ptr<data::IPlayer> p(factory->getPlayer(name, pw));

        std::unique_ptr<TCPMessageUser> umsg(new TCPMessageUser);
        if (!umsg->createQueryMessage(QUERY_MSG_TYPE_USER::REGISTER_QUERY, p))
            return false;

        boost::unique_lock<boost::mutex> l(handshake);

        networkController.send(*umsg);

        messageQueue[umsg->getMsgKey()] = std::move(umsg);
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
        // Should normally be connected
        if (!networkController.isConnected())
            networkController.connect();

        boost::unique_lock<boost::mutex> l(handshake);

        if (!localPlayer)
            return false;

        // Create message
        std::unique_ptr<TCPMessageUser> umsg(new TCPMessageUser);
        if (!umsg->createQueryMessage(QUERY_MSG_TYPE_USER::GET_PLAYERS_QUERY, localPlayer))
            return false;

        // Logout player: Send message
        networkController.send(*umsg);

        messageQueue[umsg->getMsgKey()] = std::move(umsg);
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
        TCPConnection *con = dynamic_cast<TCPConnection*>(sub);

        if (con->isActive()) {
            std::unique_ptr<TCPMessage> msg = con->getLastMessage();
            if (!msg)
                return; // Message was already handled

            std::cout << msg->toString() << std::endl;

            // Check message
            TCPMessageUser umsg;

            boost::unique_lock<boost::mutex> l(handshake);

            // When the manager is waiting for this message (check messageQueue)

            // User message
            if (umsg.createMessage(msg->getFrameData())) {
                if (umsg.isValid()) {
                    if (isWaitingFor(umsg.getMsgKey()))
                        handleUserMessage(umsg);
                }
            }
        }
    }

    void GameManagerNetworkClient::handleUserMessage(TCPMessageUser& umsg)
    {
        if (umsg.getQueryType() == QUERY_MSG_TYPE_USER::REGISTER_QUERY) {
            if (umsg.getAckStatus()) {
                // TODO: How to notify?
            }
        } else if (umsg.getQueryType() == QUERY_MSG_TYPE_USER::LOGIN_QUERY) {
            if (umsg.getAckStatus()) {
                if (localPlayer)
                    localPlayer->setLoggedIn(true);
            } else
                localPlayer.reset();
        } else if (umsg.getQueryType() == QUERY_MSG_TYPE_USER::LOGOUT_QUERY) {
            if (umsg.getAckStatus()) {
                if (localPlayer)
                    localPlayer.reset();
            }
        } else if (umsg.getQueryType() == QUERY_MSG_TYPE_USER::GET_PLAYERS_QUERY) {
            if (umsg.getAckStatus()) {
                clearPlayers();
                //clearGames();
                //players = umsg.getPlayers();
                //games = umsg.getGames();
            }
        }
    }

    bool GameManagerNetworkClient::isWaitingFor(int key)
    {
        try {
            messageQueue.at(key);

            // Waiting for this message
            messageQueue.erase(key);
            return true;
        } catch (std::out_of_range& e) {
            // Not waiting for this message
            return false;
        }
    }

}
