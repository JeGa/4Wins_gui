#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H 

// MinGW/Boost/Python problem
#undef hypot

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

namespace controller
{
	using boost::asio::ip::tcp;

    class ClientNetworkController
    {
    private:
        boost::asio::io_service io_service;
        tcp::resolver::iterator endpoint_iterator;
        int port = 9999;
        
    public:
        ClientNetworkController();
        virtual ~ClientNetworkController();
        
        void connect();

    };

}

#endif // NETWORKMANAGER_H
