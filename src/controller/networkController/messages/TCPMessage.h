/*
* Messages are used to encapsulate the TCP data to send over
* the network. They provide a abstraction for the different commands
* and are easier to use as rare data.
* 
* 
* There are to types of messages: QUERY and ACK
* All messages require a QUERY/ACK message pair:
* 
* QUERY:
* Is sent to the other side to query for data and information.
* 
* ACK:
* Is the acknowledgement for a QUERY message. A ACK message
* contains the data from the QUERY and the acknowledge data.
* 
* Each QUERY/ACK pair has a sender-unique identifier. One exception
* is the keep alive message. For that there is no QUERY/ACK needed.
* 
* 
* A message is constructed as internalData string: 
* [[HEADER] [MSG_KEY] [TYPE] [QUERY_USER_DATA] [ACK_USER_DATA] [FOOTER]]
*/

#ifndef TCPMESSAGE_H
#define TCPMESSAGE_H

#include <string>

namespace controller
{
	
	enum class MSG_TYPE
	{
		NOT_SET = 0, UNDEF = 1, KEEP_ALIVE = 2, QUERY = 3, ACK = 4
	};
	
	enum class QUERY_MSG_TYPE
	{
		NOT_SET = 0,
        NEW_GAME_QUERY,
        LOGIN_QUERY,
        LOGOUT_QUERY,
        REGISTER_QUERY,
        INPUT_QUERY,
        GET_PLAYERS_QUERY,
        GET_GAMES_QUERY
	};
    
    enum class ACK_MSG_TYPE
	{
		NOT_SET = 0,
		NEW_GAME_ACK,
        LOGIN_ACK,
        LOGOUT_ACK,
        REGISTER_ACK,
        INPUT_ACK,
        GET_PLAYERS_ACK,
        GET_GAMES_ACK
	};
    
    class TCPMessage
    {
    private:
        static int msgKeyCounter; // Unique identifier counter
        
        static const std::string HEADER;
        static const std::string FOOTER;
		
        int msgKey = -1;
        MSG_TYPE type = MSG_TYPE::NOT_SET;
        std::string queryUserData = ""; // What the client sends
        std::string ackUserData = ""; // What the server sends back
        
		// If this message has valid data
        bool valid = false;
       
        // The send string with the frame (client and server data)
        std::string internalData = "";
        
        void buildFrameData();
        bool parseFrameData(std::string data);
    public:
		static const std::string KEEP_ALIVE_MESSAGE;
	
        TCPMessage();
        virtual ~TCPMessage();
		
		// Create message to QUERY for data. The data string is encapsulated
		// with the TCPMessage frame.
		bool createQueryMessage(std::string data);
		
		// Create a ACK message as answer for a QUERY message. The data string
		// received has a TCPMessage frame.
		bool createAckMessage(std::string frameData);
		bool setAckMessage(std::string data);
		
		// Create a keep-alive message
		bool createKeepAliveMessage();
		
		// Only creates a messag based on a frame data string
		bool createMessage(std::string frameData);
        
        MSG_TYPE getType();
        std::string getFrameData(); // Return the data with the frame (to send)
        std::string getQueryUserData();
        std::string getAckUserData();
        int getMsgKey();
        
        bool isValid();
		// This resets the message to create a new message. Normally the user
		// is prevented from creating a new message if the object is already
		// a valid message (to prevent loss of message information).
		void reset();
        
        std::string toString();
    };

}

#endif // TCPMESSAGE_H
