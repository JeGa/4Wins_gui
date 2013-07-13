#include "ServerNetworkController.h"
#include <iostream>

namespace controller
{

    ServerNetworkController::ServerNetworkController()
    {
    }

    ServerNetworkController::~ServerNetworkController()
    {
    }
    
    void ServerNetworkController::startServer()
    {
        try {
            
            boost::asio::ip::tcp::acceptor acceptor(io_service,
                boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
        
            for (;;) {
                boost::asio::ip::tcp::socket socket(io_service);
                
                
                acceptor.accept(socket);

                std::string message = "Hello here is the server";

                boost::system::error_code ignored_error;
                boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
            }
            
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
        
    }

}

