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
        this->cleanerThreadHandle =
            boost::thread(&NetworkControllerServer::connectionCleanerThread,
            this);
    }
    
    void NetworkControllerServer::stopServer()
    {
        // Stop waiting for incoming connections
        acceptorThreadHandle.interrupt();
        acceptorThreadHandle.join();
        
        // Stop cleaner thread
        cleanerThreadHandle.interrupt();
        cleanerThreadHandle.join();
        
        // Remove saved client connections
        this->connections.clear();
    }
    
    std::vector<std::unique_ptr<TCPConnection>>&
        NetworkControllerServer::getConnections()
    {
        return connections;
    }
    
    void NetworkControllerServer::setExternalTCPConnectionObserver(util::Observer *o)
    {
        obs.push_back(o);
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
//            std::cout << "=> There are " << connections.size() <<
//                " connections." << std::endl;
            
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
                for (auto i : obs)
                    con->addObserver(i);
                
                con->startConnectionThreads();
                this->connections.push_back(std::move(con));
                
            } catch (std::exception& e) {
                if (!boost::asio::error::would_block)
                    std::cerr << e.what() << std::endl;
            }
        }
        
        std::cout << "=> Acceptor thread closing" << std::endl;
    }
    
    void NetworkControllerServer::connectionCleanerThread()
    {
        std::cout << "=> Cleaner thread started" << std::endl;
        
        while (true) {
            try {
                boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
            } catch (boost::thread_interrupted& e) {
                // Close thread
                break;
            }
            
            // Check if a connection is closed from a client
            
            boost::unique_lock<boost::mutex> l(cleanerMutex);

            if (!clean)
                cleanerCond.wait_for(l, boost::chrono::milliseconds(100));
            
            if (clean) { // Check again because of timed wait
                // The cond. is true
            
                // Clean connection
                std::cout << "=> Cleaning closed connection" << std::endl;
            
                std::vector<std::unique_ptr<TCPConnection>>::iterator rem;
                for (rem = connections.begin(); rem < connections.end();
                    rem++) {
                    
                    if ((*rem).get() == clean) {
                        connections.erase(rem);
                    }
                }
                
                clean = nullptr;
                
                // Then ext threads can notify this thread
                waitForCleanedMutex.unlock();
            }
        }
        
        std::cout << "=> Cleaner thread closing" << std::endl;
    }
    
    // Notified from the TCPConnection receive thread
    void NetworkControllerServer::notify(util::Subject *sub)
    {
        TCPConnection *con = static_cast<TCPConnection *>(sub);
        
        // Connection is closed:
        if (!con->isActive()) {
            // Remove from list: Notify cleaner thread
            
            waitForCleanedMutex.lock();
            
            cleanerMutex.lock();
            clean = con;
            cleanerCond.notify_one();
            cleanerMutex.unlock();
        }
    }
    
}