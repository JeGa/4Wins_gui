#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

// MinGW/Boost/Python problem
#undef hypot

#include "TCPConnection.h"
#include "Observer.h"
#include "TCPMessage.h"
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace controller
{
    using boost::asio::ip::tcp;

    class NetworkControllerClient
    {
        private:
            boost::asio::io_service io_service;
            boost::asio::io_service::work work;

            /*
             * Shared, because the io_service needs a pointer too,
             * for outstanding handler invocations at destruction.
             * (given to the handlers through boost::bind)
             */
            std::shared_ptr<TCPConnection> con;

            tcp::resolver::iterator endpoint_iterator;
            std::string port;
            std::string address;

            std::vector<boost::thread> threadHandles;

            /*
             * Observers to set for the TCPConnection.
             * Be careful with the mm here.
             */
            std::vector<util::Observer*> obs;

            void startTCPConnection(std::unique_ptr<tcp::socket> clientCon);
            void startThreads(int count = 1);
            void stopThreads();

        public:
            NetworkControllerClient(
                std::string addr = "127.0.0.1",
                std::string port = "9999");
            virtual ~NetworkControllerClient();

            void setExternalTCPConnectionObserver(util::Observer *o);

            bool ping();
            void connect();
            void disconnect();

            void send(TCPMessage& msg);

            bool isConnected();
    };

}

#endif // NETWORKMANAGER_H
