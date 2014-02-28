#include "TCPConnection.h"
#include <iostream>
#include <boost/chrono.hpp>

namespace controller
{

    const int TCPConnection::KEEP_ALIVE_TIME_SEND_SECONDS = 10;
    const int TCPConnection::KEEP_ALIVE_TIME_CHECK_SECONDS = 2;

    TCPConnection::TCPConnection(std::unique_ptr<tcp::socket> s) :
        socket(std::move(s)),
        checkKeepAliveTimer(socket->get_io_service(),
                            boost::posix_time::seconds(KEEP_ALIVE_TIME_CHECK_SECONDS)),
        sendKeepAliveTimer(socket->get_io_service(),
                           boost::posix_time::seconds(KEEP_ALIVE_TIME_SEND_SECONDS))
    {
        tcp::endpoint localEndp = socket->local_endpoint();
        localAddress = localEndp.address().to_string();
        localPort = localEndp.port();

        tcp::endpoint remoteEndp = socket->remote_endpoint();
        remoteAddress = remoteEndp.address().to_string();
        remotePort = remoteEndp.port();
    }

    TCPConnection::~TCPConnection()
    {
        closeConnectionThread();
        closeSocket();
    }

    void TCPConnection::startConnectionThread()
    {
        threadHandle = boost::thread(&TCPConnection::thread, this);

        setActive(true);
    }

    // TODO: Is this okay?
    void TCPConnection::closeConnectionThread()
    {
        // Close io service
        socket->get_io_service().stop();
        threadHandle.join();

        setActive(false);
    }

    void TCPConnection::closeSocket()
    {
        try {
            if (socket->is_open()) {
                socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
                socket->close();
            }
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    bool TCPConnection::setActive(bool status)
    {
        activeMutex.lock();
        active = status;
        activeMutex.unlock();
    }

    bool TCPConnection::isActive()
    {
        activeMutex.lock();
        bool tmp = active;
        activeMutex.unlock();
        return tmp;
    }

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

    void TCPConnection::thread()
    {
        receive();
        checkKeepAlive();
        sendKeepAlive();

        boost::asio::io_service& service = socket->get_io_service();
        service.run();
    }

    void TCPConnection::receive()
    {
        boost::asio::async_read_until(*socket, receive_buf, '\n',
                                      boost::bind(
                                          &TCPConnection::receiveHandler,
                                          this,
                                          boost::asio::placeholders::error,
                                          boost::asio::placeholders::bytes_transferred
                                      )
                                     );
    }

    void TCPConnection::receiveHandler(
        const boost::system::error_code& e,
        std::size_t size)
    {
        std::cout << "Receive Message" << std::endl;

        if (!e) {
            std::istream is(&receive_buf);
            std::string line;
            std::getline(is, line);

            std::unique_ptr<TCPMessage> msg(new TCPMessage);
            msg->createMessage(line);

            std::cout << msg->getFrameData() << std::endl;

            if (msg->isValid()) {
                if (!parseMessageInternal(*msg)) {
                    lastMessage = std::move(msg);
                    notifyObservers();
                    // Reset the last message (no observer wanted it)
                    lastMessage.release();
                }
            }
        }
        // TODO: Error codes
//        notifyObservers();

        receive();
    }

    void TCPConnection::checkKeepAlive()
    {
        checkKeepAliveTimer.async_wait(boost::bind(&TCPConnection::checkKeepAliveHandler, this));
    }

    void TCPConnection::checkKeepAliveHandler()
    {
        std::cout << "Check Keep Alive" << std::endl;

        boost::chrono::steady_clock::time_point now =
            boost::chrono::steady_clock::now();
        auto d = now - lastKeepAlive;

        if (d >= boost::chrono::seconds(KEEP_ALIVE_TIME_SEND_SECONDS + 5)) {
            // No keep alive after x seconds: Client closed the socket
            // Close thread TODO
        }

        checkKeepAliveTimer.expires_at(checkKeepAliveTimer.expires_at() +
                                       boost::posix_time::seconds(KEEP_ALIVE_TIME_CHECK_SECONDS));
        checkKeepAlive();
    }

    void TCPConnection::sendKeepAlive()
    {
        sendKeepAliveTimer.async_wait(boost::bind(&TCPConnection::sendKeepAliveHandler, this));
    }

    void TCPConnection::sendKeepAliveHandler()
    {
        std::cout << "Send Keep Alive" << std::endl;

        TCPMessage msg;
        msg.createKeepAliveMessage();
        sendMessage(msg);

        sendKeepAliveTimer.expires_at(sendKeepAliveTimer.expires_at() +
                                      boost::posix_time::seconds(KEEP_ALIVE_TIME_SEND_SECONDS));
        sendKeepAlive();
    }

// =========================================================================

// Blocking

// TODO: Synchronize

    void TCPConnection::send(std::string str)
    {
        std::cout << "Synchron send" << std::endl;

        str += "\n";
        try {
            boost::asio::write(*socket, boost::asio::buffer(str));
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void TCPConnection::sendMessage(TCPMessage& msg)
    {
        send(msg.getFrameData());
    }

// =========================================================================

// Returns true if it processed the message.
    bool TCPConnection::parseMessageInternal(TCPMessage& msg)
    {
        if (msg.getType() == MSG_TYPE::KEEP_ALIVE) {
            setKeepAlive();
            return true;
        }
        return false;
    }

    void TCPConnection::setKeepAlive()
    {
        lastKeepAlive = boost::chrono::steady_clock::now();
    }

}
