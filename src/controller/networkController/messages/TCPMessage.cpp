#include "TCPMessage.h"
#include <sstream>
#include <vector>
#include <cstdlib>

namespace controller
{
    
    const std::string TCPMessage::HEADER = "4WINS HEADER";
    const std::string TCPMessage::FOOTER = "4WINS FOOTER";
	const std::string TCPMessage::KEEP_ALIVE_MESSAGE = "4WINS ALIVE";
    int TCPMessage::msgKey = 0;

    // A new message is created, to send it over the network.
    TCPMessage::TCPMessage()
    {
    }

    TCPMessage::~TCPMessage()
    {
    }
    
    // Create and format the string to send over the network.
    bool TCPMessage::buildFrameData()
    {
        std::string frameData = "";
        
        if (queryUserData == "")
            return false;
			
		// AckUserData can be empty (for QUERY)
            
        if (type == MSG_TYPE::UNDEF || type == MSG_TYPE::NOT_SET)
            return false;
        
        std::stringstream sstr;
        sstr << static_cast<int>(msgKey);
        frameData = HEADER + ";" + sstr.str() + ";";
        sstr.str("");
		
        sstr << static_cast<int>(type);
        frameData += sstr.str() + ";" + queryUserData + ";" +
			ackUserData + ";" + FOOTER + "\n";
        
		internalData = frameData;
		
        return true;
    }
    
    // Creates this message object based on a message received from the other
    // socket (encapsulated with the TCPMessage frame).
    bool TCPMessage::parseFrameData(std::string data)
    {
        std::stringstream sstr;
        std::string tmp = "";
        std::vector<std::string> tokens;

        sstr << data;
		
        // Split by ';'
		while (std::getline(sstr, tmp, ';'))
            tokens.push_back(tmp);
        sstr.str("");
        
        if (tokens.size() != 6)
            return false;
        
        // Check Header
        if (tokens[0] != HEADER)
            return false;
            
        // Set msgKey
		tmp = tokens[1];
        int tmpKey = atoi(tmp.c_str());
        msgKey = tmpKey;
		
        // Set and check type
		tmp = tokens[2];
        int tmpInt = atoi(tmp.c_str());
        MSG_TYPE tmpType = static_cast<MSG_TYPE>(tmpInt);
		if (tmpType != MSG_TYPE::QUERY)
			return false;
		type = tmpType;
		
        // Set query data
        std::string tmpQuery = tokens[3];
		
		// Set ack data
		std::string tmpAck = tokens[4];

		if (tmpQuery.length() == 0)
			return false;
		queryUserData = tmpQuery;	
        ackUserData = tmpAck;
        
        // Check Footer
		tmp = tokens[5];
		// Remove '\n'
		tmp.erase(tmp.length()-1);
        if (tmp != FOOTER)
            return false;
			
		return true;
    }
    
    // =========================================================================
    
	bool TCPMessage::createQueryMessage(std::string data)
	{
		valid = false;
		
		if (type != MSG_TYPE::NOT_SET)
			return false;
		
		if (data.length() == 0)
			return false;
		
		queryUserData = data;
		type = MSG_TYPE::QUERY;
		
		if (!buildFrameData()) // Encapsulate in frame
			return false;
		
		msgKey++;
		
		valid = true;
		return valid;
	}
	
	bool TCPMessage::createAckMessage(std::string frameData, std::string data)
	{
		valid = false;
		
		if (type != MSG_TYPE::NOT_SET)
			return false;
			
		if (data.length() == 0)
			return false;
			
		if (!parseFrameData(frameData))
			return false;
		
		ackUserData = data;
		type = MSG_TYPE::ACK;
		valid = buildFrameData();
		
		return valid;
	}
	
	bool TCPMessage::createKeepAliveMessage()
	{
		valid = false;
		
		if (type != MSG_TYPE::NOT_SET)
			return false;
		
		type = MSG_TYPE::KEEP_ALIVE;
		queryUserData = KEEP_ALIVE_MESSAGE;
		
		valid = buildFrameData();
		return valid;
	}
	
    std::string TCPMessage::getFrameData()
    {
        return this->internalData;
    }
    
    std::string TCPMessage::getQueryUserData()
    {
        return this->queryUserData;
    }
    
    std::string TCPMessage::getAckUserData()
    {
        return this->ackUserData;
    }
    
    bool TCPMessage::isValid()
    {
        return valid;
    }

}

