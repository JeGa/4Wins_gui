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
        // Set the user data
        std::string tmp;
		std::stringstream sstr;
		
        sstr << static_cast<int>(type);
        
        if (type == QUERY_MSG_TYPE::REGISTER_QUERY) {
            
            tmp = sstr.str() + ": " + boost::lexical_cast<std::string>(p.getKey())
				+ " " + p.getName() + " " + p.getPassword();
        
        } else if (type == QUERY_MSG_TYPE::LOGIN_QUERY) {
            
            tmp = sstr.str() + ": " + boost::lexical_cast<std::string>(p.getKey())
				+ " " + p.getName() + " " + p.getPassword();
            
        } else if (type == QUERY_MSG_TYPE::LOGOUT_QUERY) {
            
            tmp = sstr.str() + ": " + boost::lexical_cast<std::string>(p.getKey())
				+ " " + p.getName();
        }
                
        return this->createQueryMessage(tmp);
    }
	
	bool TCPMessageUser::createAck(std::string frame, bool status)
	{
		std::string tmp;
		if (status)
			tmp = "SUCCESS";
		else
			tmp = "FAILURE";
		
		if (!createAckMessage(frame))
			return false;
			
		return setAckMessage(tmp);
	}

}

