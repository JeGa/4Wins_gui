#include "ClientNetworkController.h"
#include <iostream>

namespace controller
{

    ClientNetworkController::ClientNetworkController()
    {
        tcp::resolver resolver(io_service);
		
        tcp::resolver::query query("127.0.0.1", "9999");
		
        this->endpoint_iterator = resolver.resolve(query);
    }

    ClientNetworkController::~ClientNetworkController()
    {
    }

    void ClientNetworkController::connect()
    {
		
        try {
			
			std::cout << "Connectiong ..." << std::endl;
			
			tcp::socket socket(io_service);
		
			boost::asio::connect(socket, endpoint_iterator);
			
			std::cout << "Connected" << std::endl;
			
            for (;;) {
                std::vector<char> buf(128);
                boost::system::error_code error;

                size_t len = socket.read_some(boost::asio::buffer(buf), error);

                if (error == boost::asio::error::eof)
                    break; // Connection closed cleanly by peer.
                else if (error)
                    throw boost::system::system_error(error); // Some other error.

                std::cout.write(buf.data(), len);
            }
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    
}

