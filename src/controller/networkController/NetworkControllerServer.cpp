#include "NetworkControllerServer.h"
#include <iostream>
#include <boost/chrono.hpp>

namespace controller
{
    
    NetworkControllerServer::NetworkControllerServer(std::string port) :
        port(port),
        acceptor(io_service, tcp::endpoint(tcp::v4(), std::atoi(port.c_str())))
    {
        this->acceptor.non_blocking(true);
    }

    NetworkControllerServer::~NetworkControllerServer()
    {
        stopServer();
    }
    
    void NetworkControllerServer::startServer()
    {
        this->acceptorThreadHandle =
            boost::thread(&NetworkControllerServer::acceptorThread, this);
    }
    
    void NetworkControllerServer::stopServer()
    {
        // Stop waiting for incoming connections
        acceptorThreadHandle.interrupt();
        acceptorThreadHandle.join();
        
        // Remove saved client connections
        this->connections.clear();
    }
    
    std::vector<std::unique_ptr<TCPConnection>>&
        NetworkControllerServer::getConnections()
    {
        return connections;
    }
    
    // =========================================================================
    
    // The thread function
    void NetworkControllerServer::acceptorThread()
    {
        std::cout << "=> Acceptor thread started" << std::endl;
        
        while (true) {
            // Check if thread interruped
            try {
                boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
            } catch (boost::thread_interrupted& e) {
                // Close thread
                break;
            }
            
//            std::cout << "=> Wait for connection ..." << std::endl;
            
            try {
                // Wait for connection
                std::unique_ptr<tcp::socket> incomingCon(
                    new tcp::socket(io_service));
                
                // Throws exception if theres no client connection
                this->acceptor.accept(*incomingCon);
                
                std::cout << "=> Incoming connection ..." << std::endl;
                
                // Create connection
                std::unique_ptr<TCPConnection> con(
                    new TCPConnection(std::move(incomingCon)));
                con->addObserver(this);
                con->startConnectionThreads();
                this->connections.push_back(std::move(con));
                
            } catch (std::exception& e) {
                if (!boost::asio::error::would_block)
                    std::cerr << e.what() << std::endl;
            }
        }
        
        std::cout << "=> Acceptor thread closing" << std::endl;
    }
    
    // Notified from the TCPConnection receive thread
    void NetworkControllerServer::notify(util::Subject * sub)
    {
        TCPConnection *con = static_cast<TCPConnection *>(sub);
        
        // Connection is closed:
        if (!con->isActive()) {
            // Remove from list
            //this->connections.
        }
    }
    
}