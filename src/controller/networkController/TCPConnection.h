/*
* Represents a network TCP connection. For each client there is one
* TCPConnection object. Each connection listens for incoming messages
* in an own thread. A second thread sends the keep alive message to the
* remote socket.
*
* After a message is received, the TCPConnection parses the internal
* control data. After that the Observers are notified.
*/

#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

// MinGW/Boost/Python problem
#undef hypot

#include "Subject.h"
#include "TCPMessage.h"
#include <boost/asio.hpp>
#include <string>
#include <memory>
#include <boost/thread.hpp>

namespace controller
{

    using boost::asio::ip::tcp;

    class TCPConnection :
        public util::Subject,
        public std::enable_shared_from_this<TCPConnection>
    {
        private:
            boost::mutex socketMutex;
            std::unique_ptr<tcp::socket> socket;
            boost::asio::io_service& io_service;
            boost::asio::streambuf receive_buf;
            boost::asio::strand strand_receive;

            // Last received message
            std::unique_ptr<TCPMessage> lastMessage;

            bool active = false;
            boost::mutex activeMutex;

            std::string remoteAddress;
            int remotePort;
            std::string localAddress;
            int localPort;

            void receive();
            void receiveHandler(
                const boost::system::error_code& e,
                std::shared_ptr<TCPConnection> c);

            void send(std::string str);
            void sendHandler(
                const boost::system::error_code& e,
                std::shared_ptr<TCPConnection> c);

            bool setActive(bool status);
            void closeSocket();
            void stopUnsynchronized();
            void closeSocketUnsynchronized();

        public:
            TCPConnection(std::unique_ptr<tcp::socket> s);
            virtual ~TCPConnection();

            void start();
            void stop();
            void sendMessage(TCPMessage& msg);

            bool isActive();
            std::unique_ptr<TCPMessage> getLastMessage();
            int getRemotePort();
            std::string getRemoteAddress();
    };

}

#endif // TCPCONNECTION_H
