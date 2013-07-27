#ifndef TCPMESSAGEUSER_H
#define TCPMESSAGEUSER_H

#include "TCPMessage.h" // Base class: controller::TCPMessage
#include "IPlayer.h"

namespace controller
{
	
    class TCPMessageUser : public controller::TCPMessage
    {
    private:
        bool ackStatus = false; // Query successful
        
    public:
        TCPMessageUser();
        virtual ~TCPMessageUser();
        
        // Creates the message and encapsulates it with a frame
        bool createQuery(QUERY_MSG_TYPE type, data::IPlayer& p);
        // Was the query successful?
        bool createAck(std::string frame, bool status);
    };

}

#endif // TCPMESSAGEUSER_H
