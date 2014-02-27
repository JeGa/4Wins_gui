/*
* This class extends the standard TCPMessage for sending user commands
* related to a game. It extends the query and ack data with an
* additional small message protocoll:
*
* ... [QUERY_USER_DATA] [ACK_USER_DATA] ...
*
* [QUERY_USER_DATA] : "<queryType>: <information>"
* [ACK_USER_DATA] : "<ackType>: <information>"
*
* ====================================================================
*
* TCPMessageUser are:
*
* - NEW_GAME
* - INPUT
* - GET_GAMES
*
* ====================================================================
*/
#ifndef TCPMESSAGEGAME_H
#define TCPMESSAGEGAME_H

#include "TCPMessage.h" // Base class: controller::TCPMessage
#include "IPlayer.h"

namespace controller
{

    enum class QUERY_MSG_TYPE_GAME
    {
        NOT_SET = 0,
        NEW_GAME_QUERY,
        INPUT_QUERY,
        GET_GAMES_QUERY
    };

    enum class ACK_MSG_TYPE_GAME
    {
        NOT_SET = 0,
        NEW_GAME_ACK,
        INPUT_ACK,
        GET_GAMES_ACK
    };

    class TCPMessageGame : public controller::TCPMessage
    {
        private:
            GameFactory factory;

            QUERY_MSG_TYPE_GAME queryType = QUERY_MSG_TYPE_GAME::NOT_SET;
            ACK_MSG_TYPE_GAME ackType = ACK_MSG_TYPE_GAME::NOT_SET;
            bool ackStatus = false;

            // Query data (set from sender, get from receiver):
            std::shared_ptr<data::IPlayer> queryUser;

            // Ack data (set from receiver, get from sender):
            std::map<int, std::shared_ptr<data::IPlayer>> players;

        public:
            TCPMessageGame();
            virtual ~TCPMessageGame();

            QUERY_MSG_TYPE_USER getQueryType();
            bool getAckStatus();

            std::shared_ptr<data::IPlayer> getUser();
    };

}

#endif // TCPMESSAGEGAME_H
