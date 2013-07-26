#include "TCPMessage.h"
#include <sstream>
#include <vector>

namespace controller
{
    
    const std::string TCPMessage::HEADER = "4WINS HEADER";
    const std::string TCPMessage::FOOTER = "4WINS FOOTER";
    int TCPMessage::msgKey = 0;

    // A new message is created, to send it over the network.
    TCPMessage::TCPMessage()
    {
        msgKey++;
    }
    
    // Message is build from a received message string.
    // Build the message sent from the other socket.
    TCPMessage::TCPMessage(std::string data)
    {
        buildDataMessage(data);
    }

    TCPMessage::~TCPMessage()
    {
    }
    
    // Create and format the string to send over the network.
    std::string TCPMessage::buildDataFrameString()
    {
        valid = false;
        
        std::string frameData = "";
        
        if (this->clientUserData == "")
            return "";
            
        if (this->type == MSG_TYPE::UNDEF)
            return "";
        
        std::stringstream sstr;
        sstr << static_cast<int>(msgKey);
        frameData = HEADER + ";" + sstr.str() + ";";
        
        sstr.clear();
        sstr << static_cast<int>(type);
        frameData += sstr.str() + ";" + clientUserData + ";" + FOOTER + "\n";
        
        valid = true;
        
        return frameData;
    }
    
    // Creates this message object based on a message received from the other
    // socket.
    void TCPMessage::buildDataMessage(std::string data)
    {
        valid = false;
        
        std::stringstream sstr;
        std::string tmp = "";
        
        sstr << data;
        // Split by ';'
        std::vector<std::string> tokens;
        while (std::getline(sstr, tmp, ';')) {
            tokens.push_back(tmp);
        }
        sstr.clear();
        
        if (tokens.size() != 5)
            return;
        
        // Check Header
        if (tokens[0] != HEADER)
            return;
            
        // Set msgKey
        sstr << tokens[1];
        int tmpKey;
        sstr >> tmpKey;
        msgKey = tmpKey;
        sstr.clear();
            
        // Set type
        sstr << tokens[2];
        int tmpType;
        sstr >> tmpType;
        type = static_cast<MSG_TYPE>(tmpType);
        
        // set data
        tmp = tokens[3];
        clientUserData = tmp;
        
        // Check Footer
        if (tokens[4] != HEADER)
            return;
            
        if ((internalData = buildDataFrameString()) != "")
            valid = true;
    }
    
    // =========================================================================
    
    // Is not a constructor, becuause the data string has to be manipulated,
    // if inheritance is used.
    void TCPMessage::setQueryData(MSG_TYPE type, std::string data)
    {
        //!! TODO: Check if ACK
        
        this->clientUserData = data;
        this->type = type;
        this->internalData = buildDataFrameString(); // Build frame
    }
    
    std::string TCPMessage::getFrameData()
    {
        return this->internalData;
    }
    
    std::string TCPMessage::getClientUserData()
    {
        return this->clientUserData;
    }
    
    std::string TCPMessage::getServerUserData()
    {
        return this->serverUserData;
    }
    
    bool TCPMessage::isValid()
    {
        return valid;
    }

}

