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
        
        if (this->isConnected())
            return true;
        
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
        disconnect();
        
        try {
            std::unique_ptr<tcp::socket> clientCon(
                new tcp::socket(io_service));
            
			boost::asio::connect(*clientCon, endpoint_iterator);
            
            // Move ownership to TCPConnection
            // Move ownership to member unique_ptr
            con = std::unique_ptr<TCPConnection>(
                new TCPConnection(std::move(clientCon)));
            
            for (auto i : obs)
                con->addObserver(i);            
            con->startConnectionThreads();
            
			std::cout << "Client: Connected" << std::endl;
            
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    
    void NetworkControllerClient::disconnect()
    {
        if (con) {
            con->disconnect();
            con.release();
        }
    }
    
    void NetworkControllerClient::send(TCPMessage& msg)
    {
        con->sendMessage(msg);
    }
    
    std::unique_ptr<TCPMessage> NetworkControllerClient::receive()
    {   
        return con->receiveMessage();
    }
    
    void NetworkControllerClient::setExternalTCPConnectionObserver(util::Observer *o)
    {
        obs.push_back(o);
    }
    
    bool NetworkControllerClient::isConnected()
    {
        if (con)
            return true;
        return false;
    }
    
}

