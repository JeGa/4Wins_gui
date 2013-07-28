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

    TCPMessage::TCPMessage()
    {
    }

    TCPMessage::~TCPMessage()
    {
    }
    
    // Create and format the string to send over the network.
	void TCPMessage::buildFrameData()
    {
        std::string frameData = "";
        
        std::stringstream sstr;
		
        sstr << static_cast<int>(msgKey);
        frameData = HEADER + ";" + sstr.str() + ";";
        sstr.str("");
		
        sstr << static_cast<int>(type);
        frameData += sstr.str() + ";" + queryUserData + ";" +
			ackUserData + ";" + FOOTER + "\n";
        
		internalData = frameData;
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
		
		buildFrameData(); // Encapsulate in frame
		
		msgKey++;
		
		valid = true;
		return valid;
	}
	
	bool TCPMessage::createAckMessage(std::string frameData)
	{
		// TODO
		
		// REMOVE DUPLICATION FROM CREATEMSSAGE
		
		valid = false;
		
		if (type != MSG_TYPE::NOT_SET)
			return false;
			
		if (!parseFrameData(frameData))
			return false;
		
		type = MSG_TYPE::ACK;
		
		valid = true;
		return valid;
	}
	
	bool TCPMessage::setAckMessage(std::string data)
	{
		valid = false;
		
		if (type != MSG_TYPE::ACK)
			return false;
		
		if (data.length() == 0)
			return false;
			
		ackUserData = data;	
		
		buildFrameData();
		
		valid = true;
		return valid;
	}
	
	bool TCPMessage::createKeepAliveMessage()
	{
		valid = false;
		
		if (type != MSG_TYPE::NOT_SET)
			return false;
		
		type = MSG_TYPE::KEEP_ALIVE;
		queryUserData = KEEP_ALIVE_MESSAGE;
		
		buildFrameData();
		valid = true;
		return valid;
	}
	
	bool TCPMessage::createMessage(std::string frameData)
	{
		valid = false;
		
		if (type != MSG_TYPE::NOT_SET)
			return false;
			
		if (!parseFrameData(frameData))
			return false;
		
		valid = true;
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
	
	void TCPMessage::reset()
	{
		type = MSG_TYPE::NOT_SET;
		queryUserData = "";
		ackUserData = "";
		internalData = "";
		valid = false;
	}

}

