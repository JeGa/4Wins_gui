#include "TCPConnection.h"
#include <iostream>
#include <boost/chrono.hpp>

namespace controller
{

    const int TCPConnection::KEEP_ALIVE_TIME_SECONDS = 10;

    TCPConnection::TCPConnection(std::unique_ptr<tcp::socket> s)
        : socket(std::move(s))
    {
        socket->non_blocking(true);

        tcp::endpoint localEndp = socket->local_endpoint();
        localAddress = localEndp.address().to_string();
        localPort = localEndp.port();

        tcp::endpoint remoteEndp = socket->remote_endpoint();
        remoteAddress = remoteEndp.address().to_string();
        remotePort = remoteEndp.port();
    }

    TCPConnection::~TCPConnection()
    {
        disconnect();
    }

    void TCPConnection::disconnect()
    {
        // Stop the connection threads
        if (active) {
            receiveThreadHandle.interrupt(); // Closes socket and both threads
            receiveThreadHandle.join();
        }
    }

    void TCPConnection::startConnectionThreads()
    {
        sendThreadHandle =
            boost::thread(&TCPConnection::sendThread, this);

        receiveThreadHandle =
            boost::thread(&TCPConnection::receiveThread, this);

        active = true;
    }

    void TCPConnection::send(std::string str)
    {
        str += "\n";
        try {
            socketMutex.lock();
            boost::asio::write(*socket, boost::asio::buffer(str));
            socketMutex.unlock();
        } catch (std::exception& e) {
            socketMutex.unlock();
            std::cerr << e.what() << std::endl;
        }
    }

    void TCPConnection::sendMessage(TCPMessage& msg)
    {
        send(msg.getFrameData());
    }

    // Returns string "" if no message received
    std::string TCPConnection::receive()
    {
        std::string line = "";
        boost::asio::streambuf rcv;

        try {
            socketMutex.lock();

            // Throws exception if theres no client connection
            boost::asio::read_until(*socket, rcv, '\n');

            std::istream is(&rcv);
            std::getline(is, line);

            socketMutex.unlock();
        } catch (std::exception& e) {
            socketMutex.unlock();

            if (!boost::asio::error::would_block)
                std::cerr << e.what() << std::endl;
        }

        return line;
    }

    std::unique_ptr<TCPMessage>	TCPConnection::receiveMessage()
    {
        std::unique_ptr<TCPMessage> msg(new TCPMessage);
        std::string str = receive();
        if (str != "")
            msg->createMessage(str);
        return msg;
    }

    bool TCPConnection::isActive()
    {
        activeMutex.lock();
        bool tmp = active;
        activeMutex.unlock();
        return tmp;
    }

    // Returns the last message
    std::unique_ptr<TCPMessage> TCPConnection::getLastMessage()
    {
        return std::move(lastMessage);
    }

    int TCPConnection::getRemotePort()
    {
        return remotePort;
    }

    std::string TCPConnection::getRemoteAddress()
    {
        return remoteAddress;
    }

    // =========================================================================

    void TCPConnection::receiveThread()
    {
        // Initialize the keep alive value
        lastKeepAlive = boost::chrono::steady_clock::now();

        while (true) {

            // TODO: Remove busy loop!!
//            boost::this_thread::sleep_for(boost::chrono::milliseconds(500));

            // Check if thread interrupted -> Closed from other thread
            // Check if keep alive is expired -> Closed from client (or error)
            if (checkInterrupt() || !checkKeepAlive()) {

                // Close send thread
                sendThreadHandle.interrupt();
                sendThreadHandle.join();

                // Close socket
                closeSocket();

                // Close thread
                break;
            }

            // Read message
            std::unique_ptr<TCPMessage> msg = receiveMessage();

            if (msg->isValid()) {
                // CONTINUE HERE: Message received

                if (msg->getType() == MSG_TYPE::KEEP_ALIVE)
                    parseMessageInternal(*msg);
                else {
                    lastMessage = std::move(msg);
                    notifyObservers();
                    // Reset the last message (no observer wanted it)
                    lastMessage.release();
                }
            }
        }

        activeMutex.lock();
        active = false;
        activeMutex.unlock();

        // Socket is closed from client or from server
        // Notify observers:
        // - On server side, this connection is removed from the vector
        notifyObservers();
    }

    // Sends keep alive message
    void TCPConnection::sendThread()
    {
        while (true) {

            boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));

            // Check if thread interrupted -> Closed from other thread
            if (checkInterrupt()) {
                break;
            }

            TCPMessage msg;
            msg.createKeepAliveMessage();
            sendMessage(msg);
        }
    }

    // =========================================================================

    bool TCPConnection::checkKeepAlive()
    {
        boost::chrono::steady_clock::time_point now =
            boost::chrono::steady_clock::now();

        auto d = now - lastKeepAlive;

        if (d >= boost::chrono::seconds(KEEP_ALIVE_TIME_SECONDS)) {
            // No keep alive after x seconds: Client closed the socket
            return false;
        }

        return true;
    }

    void TCPConnection::parseMessageInternal(TCPMessage& msg)
    {
        // Check keep alive
        if (msg.getQueryUserData() ==
                TCPMessage::KEEP_ALIVE_MESSAGE) {
            lastKeepAlive = boost::chrono::steady_clock::now();
        }
    }

    void TCPConnection::closeSocket()
    {
        try {
            if (socket->is_open()) {
                socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
                socket->close();

                std::cout << "#> Socket closed: " <<
                          boost::this_thread::get_id() << std::endl;
            }
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    bool TCPConnection::checkInterrupt()
    {
        try {
            boost::this_thread::interruption_point();
        } catch (boost::thread_interrupted& e) {
            // Interrupted:
            return true;
        }
        return false;
    }

}
