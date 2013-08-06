/*
* This class extends the standard TCPMessage for sending user commands
* like "Login", "Logout" and "Register". It extends the query and ack
* data with an additional small message protocoll:
*
* ... [QUERY_USER_DATA] [ACK_USER_DATA] ...
* 
* [QUERY_USER_DATA] : "<queryType>: <information>"
* [ACK_USER_DATA] : "<ackType>: <information>"
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

namespace controller
{
	
    class TCPMessageUser : public controller::TCPMessage
    {
	private:
        GameFactory factory; // For player creation
    
		QUERY_MSG_TYPE queryType = QUERY_MSG_TYPE::NOT_SET;
		ACK_MSG_TYPE ackType = ACK_MSG_TYPE::NOT_SET;
		
		std::string userName = "";
		std::string userPw = "";
		std::string userKey = "";
        
        std::map<int, data::IPlayer *> players;
		
		bool ackStatus = false;

        bool tokenizeUserMessage(std::string msg, std::vector<std::string>& tokens);
        bool parseQueryUserData();
        bool parseAckUserData();
        void clearPlayers();
        void parsePlayersData();
	public:
        TCPMessageUser();
        virtual ~TCPMessageUser();
        
        // Creates the message and encapsulates it with a frame
        bool createQuery(QUERY_MSG_TYPE type, data::IPlayer& p);
        
        bool createAck(std::string frame);
		// Was the query successful?
		bool setAck(bool status);
        bool setAck(std::map<int, data::IPlayer *> &players);

		
		// Only creates a messag based on a frame data string
		bool createUserMessage(std::string frameData);
		
		QUERY_MSG_TYPE getQueryType();
		std::string getName();
		std::string getPw();
		std::string getKey();
		bool getAckStatus();
        std::map<int, data::IPlayer *> getPlayers();
    };

}

#endif // TCPMESSAGEUSER_H
