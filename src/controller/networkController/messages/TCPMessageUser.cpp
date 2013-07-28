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
	
	bool TCPMessageUser::createQuery(QUERY_MSG_TYPE type, data::IPlayer& p)
    {
        // Set the query data
        std::string tmpQueryData;
		
		std::stringstream sstr;
        sstr << static_cast<int>(type);
		
		std::string tmpKey =  boost::lexical_cast<std::string>(p.getKey());
		std::string tmpName = p.getName();
		std::string tmpPw = p.getPassword();
		std::string tmpType = sstr.str();
        
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
		if (!createAckMessage(frame))
			return false;
		
		std::string query = getQueryUserData();
		
		// Tokenize the string
		std::stringstream sstr(query);
		std::vector<std::string> tokens;
		while (sstr.good()) {
			std::string tmpStr;
			sstr >> tmpStr;
			tokens.push_back(tmpStr);
		}
		
		if (tokens.size() < 3)
			return false;
		
		if (tokens[0].length() != 2)
			return false;
		
		tokens[0].erase(1);
		
		// Query type
		int tmpTypeInt = boost::lexical_cast<int>(tokens[0]);
		QUERY_MSG_TYPE tmpType = static_cast<QUERY_MSG_TYPE>(tmpTypeInt);
		
		std::string tmpKey =  "";
		std::string tmpName = "";
		std::string tmpPw = "";
		
		if (tmpType == QUERY_MSG_TYPE::REGISTER_QUERY) {
			
			tmpKey =  tokens[1];
			tmpName = tokens[2];
			tmpPw = tokens[3];
            
			userKey = tmpKey;
			userName = tmpName;
			userPw = tmpPw;
			
			queryType = tmpType;
			ackType = ACK_MSG_TYPE::REGISTER_ACK;
        
        } else if (tmpType == QUERY_MSG_TYPE::LOGIN_QUERY) {
			
			tmpKey =  tokens[1];
			tmpName = tokens[2];
			tmpPw = tokens[3];
            
			userKey = tmpKey;
			userName = tmpName;
			userPw = tmpPw;
			
			queryType = tmpType;
			ackType = ACK_MSG_TYPE::LOGIN_ACK;

        } else if (tmpType == QUERY_MSG_TYPE::LOGOUT_QUERY) {
            
			tmpKey =  tokens[1];
			tmpName = tokens[2];
			
			userKey = tmpKey;
			userName = tmpName;
			
			queryType = tmpType;
			ackType = ACK_MSG_TYPE::LOGOUT_ACK;
			
        } else
			return false;
		
		return true;
	}
	
	bool TCPMessageUser::setAck(bool status)
	{
		std::string tmp;
		
		if (ackType == ACK_MSG_TYPE::NOT_SET)
			return false;
		
		std::stringstream sstr;
        sstr << static_cast<int>(ackType);
		tmp = sstr.str();
		
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
		
		// TODO:
		// Copy here the things from createAckmessage
		
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

