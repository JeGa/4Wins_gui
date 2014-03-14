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

            bool parseQueryUserData();

            bool parseAckUserData();
            bool parsePlayersData(std::string& playersList);

            /*
             * Functions for converting.
             */
            std::string intToString(int v);
            int stringToInt(std::string v);
            double stringToDouble(std::string v);
            std::string doubleToString(double v);

            std::string playerToMessageString(data::IPlayer& p);
            std::string queryMsgTypeUserToString(QUERY_MSG_TYPE_USER type);
            std::string ackMsgTypeUserToString(ACK_MSG_TYPE_USER type);
            QUERY_MSG_TYPE_USER stringToQueryMsgType(std::string type);
            ACK_MSG_TYPE_USER stringToAckMsgType(std::string type);
            ACK_MSG_TYPE_USER queryToAckMsgType(QUERY_MSG_TYPE_USER type);
            QUERY_MSG_TYPE_USER ackToQueryMsgType(ACK_MSG_TYPE_USER type);

            std::vector<std::string>& split(
                const std::string& s,
                char delim,
                std::vector<std::string>& elems);

            /*
             * Query data (set from sender, get from receiver)
             */
            std::shared_ptr<data::IPlayer> queryUser;

            /*
             * Ack data (set from receiver, get from sender)
             */
            std::map<int, std::shared_ptr<data::IPlayer>> players;

            // TODO: Make inherited functions private
            //bool createQueryMessage(std::string data);
            //bool setAckMessage(std::string data);

        public:
            TCPMessageUser() {} // TODO: Get factory as parameter?
            virtual ~TCPMessageUser() {}

            bool createQueryMessage(
                QUERY_MSG_TYPE_USER type,
                std::shared_ptr<data::IPlayer> p);
            bool setAckMessage(
                std::map<int, std::shared_ptr<data::IPlayer>>& players
            );
            bool setAckMessage(bool status);

            virtual bool createMessage(std::string frameData) override;
            virtual void reset() override;

            QUERY_MSG_TYPE_USER getQueryType();
            bool getAckStatus();
            std::shared_ptr<data::IPlayer> getUser();
            std::map<int, std::shared_ptr<data::IPlayer>> getPlayers();
    };

}

#endif // TCPMESSAGEUSER_H
