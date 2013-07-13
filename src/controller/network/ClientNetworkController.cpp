//#include "ClientNetworkController.h"
//#include <iostream>
////#include <boost/array.hpp>
//
//namespace controller
//{
//
//    ClientNetworkController::ClientNetworkController()
//    {
//        boost::asio::ip::tcp::resolver resolver(io_service);
//        boost::asio::ip::tcp::resolver::query query("127.0.0.1", "http");
//        this->endpoint_iterator = resolver.resolve(query);
//    }
//
//    ClientNetworkController::~ClientNetworkController()
//    {
//    }
//
//    void ClientNetworkController::connect()
//    {
//        boost::asio::ip::tcp::socket socket(io_service);
//        boost::asio::connect(socket, endpoint_iterator);
//
//        try {
//            for (;;) {
////                boost::array<char, 128> buf;
//                std::vector<char> buf(128);
//                boost::system::error_code error;
//
//                size_t len = socket.read_some(boost::asio::buffer(buf), error);
//
//                if (error == boost::asio::error::eof)
//                    break; // Connection closed cleanly by peer.
//                else if (error)
//                    throw boost::system::system_error(error); // Some other error.
//
//                std::cout.write(buf.data(), len);
//            }
//        } catch (std::exception& e) {
//            std::cerr << e.what() << std::endl;
//        }
//    }
//    
//}
//
