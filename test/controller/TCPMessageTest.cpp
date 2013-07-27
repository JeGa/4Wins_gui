#include "TCPMessageTest.h"
#include <iostream>

namespace controller
{
	BOOST_AUTO_TEST_SUITE(TCPMessageTestSuite)
    
    BOOST_FIXTURE_TEST_CASE(testMessageSend, TCPMessageTest)
    {
        BOOST_CHECK(!msgQuery.isValid());
        
        std::string queryData = "These are not the droids you are looking for";
        
		BOOST_CHECK(msgQuery.createQueryMessage(queryData));
        BOOST_CHECK(msgQuery.isValid());
        
        // I only look here from the console ...
        std::string setQueryData = msgQuery.getQueryUserData();
		BOOST_CHECK(queryData.compare(setQueryData) == 0);
		
        std::cout << std::endl << msgQuery.getFrameData() << std::endl;
		
		// Is not allowed:
		BOOST_CHECK(!msgQuery.createQueryMessage(queryData));
    }
    
    BOOST_FIXTURE_TEST_CASE(testMessageReceive, TCPMessageTest)
    {
        // Client side =========================================================
        // Same as send
        std::string queryData = "These are not the droids you are looking for";
        
        BOOST_CHECK(msgQuery2.createQueryMessage(queryData));
        BOOST_CHECK(msgQuery2.isValid());
        
        std::string frame = msgQuery2.getFrameData();
        
        // Server side =========================================================
        // Now in "frame" there is the received string
		BOOST_CHECK(msgAck.createAckMessage(frame));
		BOOST_CHECK(msgAck.setAckMessage("I dont look for droids"));
        BOOST_CHECK(msgAck.isValid());
        
		std::cout << "Query msg: " << std::endl << frame << std::endl;
		std::cout << "Ack msg: " << std::endl << msgAck.getFrameData() << std::endl;
    
		// Is not allowed:
		BOOST_CHECK(!msgAck.createAckMessage(frame));
	}
    
    BOOST_AUTO_TEST_SUITE_END()

}