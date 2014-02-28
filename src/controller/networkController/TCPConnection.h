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
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>
#include <memory>

namespace controller
{

    using boost::asio::ip::tcp;

    class TCPConnection : public util::Subject
    {
        private:
            static const int KEEP_ALIVE_TIME_SEND_SECONDS;
            static const int KEEP_ALIVE_TIME_CHECK_SECONDS;

            boost::thread threadHandle;

            std::unique_ptr<tcp::socket> socket;

            boost::asio::streambuf receive_buf;
            boost::asio::deadline_timer checkKeepAliveTimer;
            boost::asio::deadline_timer sendKeepAliveTimer;
            boost::chrono::steady_clock::time_point lastKeepAlive;

            // Last received message
            std::unique_ptr<TCPMessage> lastMessage;

            bool active = false;
            boost::mutex activeMutex;

            std::string remoteAddress;
            int remotePort;
            std::string localAddress;
            int localPort;

            void thread();

            void receive();
            void receiveHandler(const boost::system::error_code& e,
                               std::size_t size);

            void checkKeepAlive();
            void checkKeepAliveHandler();

            void sendKeepAlive();
            void sendKeepAliveHandler();

            void send(std::string str);

            bool parseMessageInternal(TCPMessage& msg);
            void setKeepAlive();
            bool setActive(bool status);

            void closeConnectionThread();
            void closeSocket();

        public:
            TCPConnection(std::unique_ptr<tcp::socket> s);
            virtual ~TCPConnection();

            void startConnectionThread();
            void sendMessage(TCPMessage& msg);

            bool isActive();
            std::unique_ptr<TCPMessage> getLastMessage();
            int getRemotePort();
            std::string getRemoteAddress();
    };

}

#endif // TCPCONNECTION_H
