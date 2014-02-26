#ifndef SERVERNETWORKCONTROLLER_H
#define SERVERNETWORKCONTROLLER_H

// MinGW/Boost/Python problem
#undef hypot

#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "TCPConnection.h"
#include "Observer.h"

namespace controller
{
	
	using boost::asio::ip::tcp;
	
    class NetworkControllerServer : public util::Observer
    {
    private:
        boost::asio::io_service io_service;
        tcp::acceptor acceptor;
        std::string port;
        boost::thread acceptorThreadHandle;
        boost::thread cleanerThreadHandle;
        
        boost::condition_variable cleanerCond;
        boost::mutex cleanerMutex;
        boost::mutex waitForCleanedMutex;
        TCPConnection *clean = nullptr;

        // Holds all client connections
        std::vector<std::unique_ptr<TCPConnection>> connections;
        
        // Observers to set for each TCPConnection
        std::vector<util::Observer*> obs;
        //!! Be careful here!
        
        // This thread waits for incoming connections
        void acceptorThread();
        void connectionCleanerThread();
        
    public:
        NetworkControllerServer(std::string port = "9999");
        virtual ~NetworkControllerServer();
        
        void setExternalTCPConnectionObserver(util::Observer *o);
        
        void startServer();
        void stopServer();
        std::vector<std::unique_ptr<TCPConnection>>& getConnections();
        
        virtual void notify(util::Subject *sub);
    };

}

#endif // SERVERNETWORKCONTROLLER_H
