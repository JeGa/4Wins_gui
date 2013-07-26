/*
* A message is constructed as:
* 
* internalData string: [[HEADER] [MSG_KEY] [TYPE] [USER_DATA] [FOOTER]]
*/

#ifndef TCPMESSAGE_H
#define TCPMESSAGE_H

#include <string>

namespace controller
{
    
    enum class MSG_TYPE {
        UNDEF, KEEP_ALIVE, // This msg
        NEW_GAME_QUERY, NEW_GAME_ACK, // Game
        LOGIN_QUERY, LOGIN_ACK, // User
        LOGOUT_QUERY, LOGOUT_ACK, // User
        REGISTER_QUERY, REGISTER_ACK, // User
        INPUT_QUERY, INPUT_ACK}; // Input
    
    class TCPMessage
    {
    private:
        static int msgKey;
        static const std::string HEADER;
        static const std::string FOOTER;
        MSG_TYPE type = MSG_TYPE::UNDEF;
        std::string clientUserData = ""; // What the client sends
        std::string serverUserData = ""; // What the server sends
        
        bool valid = false;
       
        // The send string with the frame (client and server data)
        std::string internalData = "";
        
        std::string buildDataFrameString();
        void buildDataMessage(std::string data);
    public:
        TCPMessage(); // To send data
        TCPMessage(std::string data); // Received data with frame
        virtual ~TCPMessage();
        
        std::string getFrameData();
        std::string getClientUserData();
        std::string getServerUserData();
        
        void setQueryData(MSG_TYPE type, std::string data); // data without frame
        bool isValid();
    };

}

#endif // TCPMESSAGE_H
