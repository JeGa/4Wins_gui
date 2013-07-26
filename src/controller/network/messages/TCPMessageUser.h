//#ifndef TCPMESSAGEUSER_H
//#define TCPMESSAGEUSER_H
//
//#include "TCPMessage.h" // Base class: controller::TCPMessage
//#include "IPlayer.h"
//
//namespace controller
//{
//
//    class TCPMessageUser : public controller::TCPMessage
//    {
//    private:
//        bool ackStatus = false; // Query successful
//        
//    public:
//        
//        TCPMessageUser();
//        virtual ~TCPMessageUser();
//        
//        // Creates the message and encapsulates it with a frame
//        bool createQuery(MSG_TYPE type, data::IPlayer& p);
//        // Extracts the data from the string to a the message object
//        bool createAck(std::string data);
//    };
//
//}
//
//#endif // TCPMESSAGEUSER_H
