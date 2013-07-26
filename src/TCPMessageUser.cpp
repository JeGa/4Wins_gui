//#include "TCPMessageUser.h"
//
//namespace controller
//{
//
//    TCPMessageUser::TCPMessageUser(MSG_TYPE type, data::IPlayer& p)
//    {
//        // Set the user data
//        std::string tmp;
//        
//        if (type == MSG_TYPE::REGISTER_QUERY) {
//            
//            tmp = p.getKey() + ": " + p.getName() + " " + p.getPassword();
//        
//        } else if (type == MSG_TYPE::REGISTER_ACK) {
//            
//            mp = p.getKey() + ": " + p.getName();
//            
//        }
//
////            type == MSG_TYPE::REGISTER_ACK ||
////            type == MSG_TYPE::LOGIN_ACK ||
////            type == MSG_TYPE::LOGIN_QUERY ||
////            type == MSG_TYPE::LOGOUT_ACK ||
////            type == MSG_TYPE::LOGOUT_QUERY) {
//                
//            //tmp = p.getKey() + p.;
//                
//        this->setUserData(type, tmp);
//    }
//    
//    TCPMessageUser::TCPMessageUser(std::string data)
//    {
//        this->setFrameData(data);
//        
//        // Extract the user data
//    }
//
//    TCPMessageUser::~TCPMessageUser()
//    {
//    }
//
//}
//
