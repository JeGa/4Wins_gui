#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H 

// MinGW/Boost/Python problem
#undef hypot

#include "TCPConnection.h"
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

namespace controller
{
	using boost::asio::ip::tcp;

    class NetworkControllerClient
    {
    private:
        boost::asio::io_service io_service;
        
        std::unique_ptr<TCPConnection> con;
        
        tcp::resolver::iterator endpoint_iterator;
        std::string port;
        std::string address;
        
    public:
        NetworkControllerClient(std::string addr = "127.0.0.1",
            std::string port = "9999");
        virtual ~NetworkControllerClient();
        
        bool ping(); // Only try if the server is online
        void connect();
        void disconnect();
        
        void send(std::string str);
        std::string receive();
        
//        std::string getData();
    };

}

#endif // NETWORKMANAGER_H
