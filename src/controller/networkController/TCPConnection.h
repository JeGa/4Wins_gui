/*
* Represents a network TCP connection. For each client there is one
* TCPConnection object. Each connection listens for incoming messages
* in an own thread. A second thread sends the keep alive message to the
* remote socket. To send and receive manually, the public send() and
* receive() functions can be used: The socket is protected with a mutex.
*/

#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

// MinGW/Boost/Python problem
#undef hypot

#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <string>
#include "Subject.h"
#include "TCPMessage.h"

namespace controller
{

    using boost::asio::ip::tcp;

    class TCPConnection : public util::Subject
    {
    private:
        static const int KEEP_ALIVE;
    
        boost::thread receiveThreadHandle;
        boost::thread sendThreadHandle;
        
        std::unique_ptr<tcp::socket> socket;
        boost::mutex socketMutex;
        boost::chrono::steady_clock::time_point lastKeepAlive;
        
        bool active = true;
        boost::mutex activeMutex;
        std::string remoteAddress;
        int remotePort;
        std::string localAddress;
        int localPort;
        
        void sendThread();
        void receiveThread();
        
        void parseMessageInternal(std::string str);
        bool checkKeepAlive();
        void closeSocket();
        bool sleepAndCheckInterrupt();
    public:
        TCPConnection(std::unique_ptr<tcp::socket> s);
        virtual ~TCPConnection();

        void startConnectionThreads(); // Start receiving and keep alive
        
        void send(std::string str);
        std::string receive();
        
        void sendMessage(TCPMessage& msg);
        //TCPMessage receiveMessage(); //!! TODO
        
        // If threads are running, closes the threads and the socket
        void disconnect();
        bool isActive();
    };

}

#endif // TCPCONNECTION_H
