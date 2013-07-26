#include "TCPMessageTest.h"
#include <iostream>

namespace controller
{
	BOOST_AUTO_TEST_SUITE(TCPMessageTestSuite)
    
    BOOST_FIXTURE_TEST_CASE(testMessageSend, TCPMessageTest)
    {
        BOOST_CHECK(!msg.isValid());
        
        std::string queryRegister = "These are not the droids you are looking for";
        
        msg.setQueryData(MSG_TYPE::REGISTER_QUERY, queryRegister);
        BOOST_CHECK(msg.isValid());
        
        // I only look here from the console ...
        std::string frame = msg.getFrameData();
        std::cout << std::endl << frame << std::endl;
    }
    
    BOOST_FIXTURE_TEST_CASE(testMessageReceive, TCPMessageTest)
    {
        // Client side =========================================================
        // Same as send
        std::string queryRegister = "These are not the droids you are looking for";
        
        msg.setQueryData(MSG_TYPE::REGISTER_QUERY, queryRegister);
        BOOST_CHECK(msg.isValid());
        
        std::string frame = msg.getFrameData();
        
        // Server side =========================================================
        // Now in "frame" there is the received string
        TCPMessage msgRec(frame);
        BOOST_CHECK(msg.isValid());
        
        // Now both msg should be the same
        BOOST_CHECK(!msgRec.getClientUserData().compare(queryRegister));
       // BOOST_CHECK(!msgRec.getFrameData().compare(frame));
        
        std::cout << std::endl << msgRec.getClientUserData() << std::endl;
        std::cout << std::endl << msgRec.getFrameData() << std::endl;
        
        // To resend the message to the client:
        //msgRec.setQueryData(MSG_TYPE::REGISTER_ACK, )
    }
    
    BOOST_AUTO_TEST_SUITE_END()

}

