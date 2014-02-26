#include "GameManagerNetworkServer.h"

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

    void GameManagerNetworkServer::logoutPlayer(std::string name, std::string pw)
    {
        // Set logged-in to false
        playerStatus(name, pw, false);
    }

    void GameManagerNetworkServer::loginPlayer(std::string name, std::string pw)
    {
        // Set logged-in to true
        playerStatus(name, pw, true);
    }

    void GameManagerNetworkServer::playerStatus(
        std::string name, std::string pw, bool playerStatus)
    {
        players[addPlayer(name, pw)]->setLoggedIn(playerStatus);
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
        TCPConnection *con = static_cast<TCPConnection*>(sub);

        if (con->isActive()) {
            std::unique_ptr<TCPMessage> msg = con->getLastMessage();
            if (!msg)
                return;

            std::cout << msg->toString() << std::endl;

            // Check message type
            TCPMessageUser umsg;

            // Is it a user message
            if (umsg.createMessage(msg->getFrameData())) {
                if (umsg.isValid())
                    handleUserMessage(con, umsg);
            }
        }
    }

    void GameManagerNetworkServer::handleUserMessage(TCPConnection *con, TCPMessageUser& umsg)
    {
        std::shared_ptr<data::IPlayer> p(umsg.getUser());

        if (umsg.getQueryType() == QUERY_MSG_TYPE_USER::REGISTER_QUERY) {

            addPlayer(p->getName(), p->getPassword());
            umsg.setAckMessage(true); // TODO: Validation

            con->sendMessage(umsg);

        } else if (umsg.getQueryType() == QUERY_MSG_TYPE_USER::LOGIN_QUERY) {

            loginPlayer(p->getName(), p->getPassword());
            umsg.setAckMessage(true); // TODO: Validation

            con->sendMessage(umsg);

        } else if (umsg.getQueryType() == QUERY_MSG_TYPE_USER::LOGOUT_QUERY) {

            logoutPlayer(p->getName(), p->getPassword());
            umsg.setAckMessage(true); // TODO: Validation

            con->sendMessage(umsg);

        } else if (umsg.getQueryType() == QUERY_MSG_TYPE_USER::GET_PLAYERS_QUERY) {

            //umsg.setAckMessage(players);

            con->sendMessage(umsg);

        }
    }

}
