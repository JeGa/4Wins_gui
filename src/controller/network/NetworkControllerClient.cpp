#include "NetworkControllerClient.h"
#include <iostream>

namespace controller
{

    NetworkControllerClient::NetworkControllerClient(std::string addr, std::string port)
        : address(addr), port(port)
    {
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(address, port);
		
        // DNS resolve
        endpoint_iterator = resolver.resolve(query);
    }

    NetworkControllerClient::~NetworkControllerClient()
    {
        disconnect();
    }
    
    bool NetworkControllerClient::ping()
    {
        bool status = true;
        
        connect();
        
        // If error connecting to server
        if (!con)
            status = false;
        else
            disconnect();
        
        return status;
    }

    void NetworkControllerClient::connect()
    {
        if (con)
            if (con->isActive()) {
                con->disconnect();
                con.release();
            }
        
        try {
            std::unique_ptr<tcp::socket> clientCon(
                new tcp::socket(io_service));
            
			boost::asio::connect(*clientCon, endpoint_iterator);
            
            // Move ownership to TCPConnection
            // Move ownership to member unique_ptr
            con = std::unique_ptr<TCPConnection>(
                new TCPConnection(std::move(clientCon)));
            
            con->startConnectionThreads();
            
			std::cout << "Client: Connected" << std::endl;
            
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    
    void NetworkControllerClient::disconnect()
    {
        con->disconnect();
    }
    
    void NetworkControllerClient::send(std::string str)
    {
        con->send(str);
    }
    
    std::string NetworkControllerClient::receive()
    {   
        return con->receive();
    }
    
}

