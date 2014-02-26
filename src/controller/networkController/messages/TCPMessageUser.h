/*
* This class extends the standard TCPMessage for sending user commands
* related to a player. It extends the query and ack data with an
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
* - LOGIN
* - LOGOUT
* - REGISTER
* - GET_PLAYERS
*
* ====================================================================
*
* This class is not responsible for the memory management of players map!
*/

#ifndef TCPMESSAGEUSER_H
#define TCPMESSAGEUSER_H

#include "TCPMessage.h" // Base class: controller::TCPMessage
#include "IPlayer.h"
#include "GameFactory.h"
#include <vector>
#include <map>
#include <memory>

namespace controller
{

    enum class QUERY_MSG_TYPE_USER
    {
        NOT_SET = 0,
        LOGIN_QUERY,
        LOGOUT_QUERY,
        REGISTER_QUERY,
        GET_PLAYERS_QUERY
    };

    enum class ACK_MSG_TYPE_USER
    {
        NOT_SET = 0,
        LOGIN_ACK,
        LOGOUT_ACK,
        REGISTER_ACK,
        GET_PLAYERS_ACK
    };

    class TCPMessageUser : public controller::TCPMessage
    {
        private:
            GameFactory factory;

            QUERY_MSG_TYPE_USER queryType = QUERY_MSG_TYPE_USER::NOT_SET;
            ACK_MSG_TYPE_USER ackType = ACK_MSG_TYPE_USER::NOT_SET;
            bool ackStatus = false;

            bool tokenizeUserMessage(std::string msg, std::vector<std::string>& tokens);
            bool parseQueryUserData();
            bool parseAckUserData();
            void clearPlayers();
            void parsePlayersData();

            // Query data (set from sender, get from receiver):
            std::shared_ptr<data::IPlayer> queryUser;

            // Ack data (set from receiver, get from sender):
            std::map<int, std::shared_ptr<data::IPlayer>> players;

        public:
            TCPMessageUser() {} // TODO: Get factory as parameter?
            virtual ~TCPMessageUser() {}

            // Override/overload
            bool createQueryMessage(
                QUERY_MSG_TYPE_USER type,
                std::shared_ptr<data::IPlayer> p);
            bool createMessage(std::string frameData);
            bool setAckMessage(bool status);
            bool setAckMessage(
                std::map<int, std::shared_ptr<data::IPlayer>>& players);
            void reset();

            QUERY_MSG_TYPE_USER getQueryType();
            bool getAckStatus();

            std::shared_ptr<data::IPlayer> getUser();
            std::map<int, std::shared_ptr<data::IPlayer>> getPlayers();
    };

}

#endif // TCPMESSAGEUSER_H
