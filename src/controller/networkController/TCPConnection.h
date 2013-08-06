/*
* Represents a network TCP connection. For each client there is one
* TCPConnection object. Each connection listens for incoming messages
* in an own thread. A second thread sends the keep alive message to the
* remote socket. To send and receive manually, the public send() and
* receive() functions can be used: The socket is protected with a mutex.
* 
* After a message is received, the TCPConnection parses the internal
* control data. After that the Observers are notified.
* 
* ==============================================================================
* 
* NOT IMPLEMENTED:
* 
* There are two different receive modes available:
* 
* AUTO_RECEIVE:
* 
* Messages are received in a receiver-thread. This is the standard mode.
* In this mode the clients can receive status and control messages from
* the server. When a messages is received, all observers are notified
* from the receive-thread.
* 
* MANUAL_RECEIVE:
* 
* Messages are only received, if the receive() method is invoked.
* This is useful for the send-receive handshake. For example, this mode
* is enabled when sending register_user messages:
* sendMsg()
* rcvMsg()
* Both functions are called from the same thread, so there are no
* synchronisation mechanics needed.
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
#include <memory>

namespace controller
{

//    enum class RECEIVE_MODE
//    {
//        AUTO_RECEIVE, MANUAL_RECEIVE
//    }
    
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
        
        bool active = false;
        boost::mutex activeMutex;
        
        std::string remoteAddress;
        int remotePort;
        std::string localAddress;
        int localPort;
        
        // Last received message
        std::unique_ptr<TCPMessage> lastMessage;
        
        void sendThread();
        void receiveThread();
        
        void parseMessageInternal(TCPMessage& msg);
        bool checkKeepAlive();
        void closeSocket();
        bool checkInterrupt();

        void send(std::string str);
        std::string receive();
        
        // Mode
//        RECEIVE_MODE receiveMode = RECEIVE_MODE::AUTO_RECEIVE;
    public:
        TCPConnection(std::unique_ptr<tcp::socket> s);
        virtual ~TCPConnection();

        void startConnectionThreads(); // Start receiving and keep alive
        
        void sendMessage(TCPMessage& msg);
        std::unique_ptr<TCPMessage> receiveMessage();
        
        // If threads are running, closes the threads and the socket
        void disconnect();
        bool isActive();
//        void setReceiveMode(RECEIVE_MODE m);
        
        std::unique_ptr<TCPMessage> getLastMessage();
        int getRemotePort();
        std::string getRemoteAddress();
    };

}

#endif // TCPCONNECTION_H
