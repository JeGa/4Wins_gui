#include "TCPMessageUser.h"

#include <boost/lexical_cast.hpp>
#include <sstream>
#include <cstdlib>

namespace controller
{

    TCPMessageUser::TCPMessageUser()
	{
	}
	
	TCPMessageUser::~TCPMessageUser()
    {
    }
	
    // =========================================================================
    
	bool TCPMessageUser::createQuery(QUERY_MSG_TYPE type, data::IPlayer& p)
    {
        // Set the query data
        std::string tmpQueryData;
        int typeInt = static_cast<int>(type);
		
		std::string tmpKey =  boost::lexical_cast<std::string>(p.getKey());
		std::string tmpName = p.getName();
		std::string tmpPw = p.getPassword();
		std::string tmpType = boost::lexical_cast<std::string>(typeInt);
        
        if (type == QUERY_MSG_TYPE::REGISTER_QUERY) {
            
            tmpQueryData = tmpType + ": " + tmpKey + " " + tmpName + " " + tmpPw;
        
        } else if (type == QUERY_MSG_TYPE::LOGIN_QUERY) {
            
            tmpQueryData = tmpType + ": " + tmpKey + " " + tmpName + " " + tmpPw;
            
        } else if (type == QUERY_MSG_TYPE::LOGOUT_QUERY) {
            
            tmpQueryData = tmpType + ": " + tmpKey + " " + tmpName;
			
        } else
			return false;
		
		queryType = type;
		userKey = tmpKey;
		userName = tmpName;
		userPw = tmpPw;
                
        return this->createQueryMessage(tmpQueryData);
    }
	
	bool TCPMessageUser::createAck(std::string frame)
	{
        // Ensures that the frame is a QUERY
		if (!createAckMessage(frame))
			return false;
            
        // Message type is now ACK, now the queryUserData has to be parsed
		
        if (!parseQueryUserData())
            return false;
            
        if (queryType == QUERY_MSG_TYPE::REGISTER_QUERY)
            ackType = ACK_MSG_TYPE::REGISTER_ACK;
        else if (queryType == QUERY_MSG_TYPE::LOGIN_QUERY)
            ackType = ACK_MSG_TYPE::LOGIN_ACK;
        else if (queryType == QUERY_MSG_TYPE::LOGOUT_QUERY)
            ackType = ACK_MSG_TYPE::LOGOUT_ACK;
        else
            return false;
        return true;
	}
	
	bool TCPMessageUser::setAck(bool status)
	{
		std::string tmp;
		
		if (ackType == ACK_MSG_TYPE::NOT_SET)
			return false;
		
        int typeTmp = static_cast<int>(ackType);
		tmp = boost::lexical_cast<std::string>(typeTmp);
		
		if (status)
			tmp += ": SUCCESS";
		else
			tmp += ": FAILURE";
			
		return setAckMessage(tmp);
	}
	
	bool TCPMessageUser::createUserMessage(std::string frameData)
	{
		if (!createMessage(frameData))
			return false;
		
        if (!parseAckUserData()) {
            if (!parseQueryUserData())
                return false;
        }
        return true;
	}
    
    // =========================================================================
    
     bool TCPMessageUser::tokenizeUserMessage(std::string msg,
        std::vector<std::string>& tokens)
    {
		// Tokenize the string
		std::stringstream sstr(msg);
		while (sstr.good()) {
			std::string tmpStr;
			sstr >> tmpStr;
			tokens.push_back(tmpStr);
		}
		
		if (tokens.size() < 2)
			return false;
		
		if (tokens[0].length() != 2)
			return false;
		
		tokens[0].erase(1);

        return true;  
    }
    
    bool TCPMessageUser::parseQueryUserData()
    {
        std::vector<std::string> tokens;

        if (!tokenizeUserMessage(getQueryUserData(), tokens))
            return false;
            
        if (tokens.size() != 4)
			return false;
        
        // Query type
		int tmpTypeInt = boost::lexical_cast<int>(tokens[0]);
        
        QUERY_MSG_TYPE tmpType;
        try {
            tmpType = static_cast<QUERY_MSG_TYPE>(tmpTypeInt);
        } catch (boost::bad_lexical_cast& e) {
            return false;
        }
        
		std::string tmpKey =  "";
		std::string tmpName = "";
		std::string tmpPw = "";
		
		if (tmpType == QUERY_MSG_TYPE::REGISTER_QUERY) {
			
			userKey =  tokens[1];
			userName = tokens[2];
			userPw = tokens[3];
			
			queryType = tmpType;
        
        } else if (tmpType == QUERY_MSG_TYPE::LOGIN_QUERY) {
			
			userKey =  tokens[1];
			userName = tokens[2];
			userPw = tokens[3];
			
			queryType = tmpType;

        } else if (tmpType == QUERY_MSG_TYPE::LOGOUT_QUERY) {
            
			userKey =  tokens[1];
			userName = tokens[2];
			
			queryType = tmpType;
			
        } else
			return false;
            
        return true;
    }
    
    bool TCPMessageUser::parseAckUserData()
    {
        std::vector<std::string> tokens;

        if (!tokenizeUserMessage(getAckUserData(), tokens))
            return false;
            
        if (tokens.size() != 2)
			return false;
        
        // Ack type
		int tmpTypeInt = boost::lexical_cast<int>(tokens[0]);
        
        ACK_MSG_TYPE tmpType;
        try {
            tmpType = static_cast<ACK_MSG_TYPE>(tmpTypeInt);
		} catch (boost::bad_lexical_cast& e) {
            return false;
        }
		
		if (tmpType == ACK_MSG_TYPE::REGISTER_ACK) {
			
            queryType = QUERY_MSG_TYPE::REGISTER_QUERY;
			ackType = tmpType;
        
        } else if (tmpType == ACK_MSG_TYPE::LOGIN_ACK) {
			
            queryType = QUERY_MSG_TYPE::LOGIN_QUERY;
			ackType = tmpType;

        } else if (tmpType == ACK_MSG_TYPE::LOGOUT_ACK) {
			
            queryType = QUERY_MSG_TYPE::LOGOUT_QUERY;
			ackType = tmpType;
        } else
			return false;
            
        if (tokens[1] == "SUCCESS")
            ackStatus = true;
        else
            ackStatus = false;
            
        return true;
    }
	
	QUERY_MSG_TYPE TCPMessageUser::getQueryType()
	{
		return queryType;
	}
	
	std::string TCPMessageUser::getName()
	{
		return userName;
	}
	
	std::string TCPMessageUser::getPw()
	{
		return userPw;
	}
	
	std::string TCPMessageUser::getKey()
	{
		return userKey;
	}
	
	bool TCPMessageUser::getAckStatus()
	{
		return ackStatus;
	}
	
}

