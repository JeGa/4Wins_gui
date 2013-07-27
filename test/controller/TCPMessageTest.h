#ifndef TCPMESSAGETEST_H
#define TCPMESSAGETEST_H

#include <boost/test/unit_test.hpp>
#include "TCPMessage.h"

namespace controller
{

    struct TCPMessageTest
    {
        TCPMessage msgQuery;
		TCPMessage msgQuery2;
		TCPMessage msgAck;
        
        TCPMessageTest() {};
        ~TCPMessageTest() {};
    };

}

#endif // TCPMESSAGETEST_H
