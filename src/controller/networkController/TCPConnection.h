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
#include <boost/date_time/posix_time/posix_time.hpp>
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
            static const int KEEP_ALIVE_TIME_SEND_SECONDS;
            static const int KEEP_ALIVE_TIME_CHECK_SECONDS;

            boost::mutex socketMutex;
            std::unique_ptr<tcp::socket> socket;

            boost::asio::io_service& io_service;

            boost::asio::streambuf receive_buf;
            boost::asio::deadline_timer checkKeepAliveTimer;
            boost::asio::deadline_timer sendKeepAliveTimer;
            boost::chrono::steady_clock::time_point lastKeepAlive;

            boost::asio::strand strand_receive;
            boost::asio::strand strand_sendKeepAlive;
            boost::asio::strand strand_checkKeepAlive;

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

            void checkKeepAlive();
            void checkKeepAliveHandler(
                const boost::system::error_code& e,
                std::shared_ptr<TCPConnection> c);

            void sendKeepAlive();
            void sendKeepAliveHandler(
                const boost::system::error_code& e,
                std::shared_ptr<TCPConnection> c);

            void send(std::string str);

            bool parseMessageInternal(TCPMessage& msg);
            void setKeepAlive();
            bool setActive(bool status);

            void closeSocket();
            void closeWaits();

        public:
            TCPConnection(
                std::unique_ptr<tcp::socket> s);
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
