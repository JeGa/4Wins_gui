#include "TCPConnection.h"
#include <iostream>

namespace controller
{

    TCPConnection::TCPConnection(std::unique_ptr<tcp::socket> s) :
        socket(std::move(s)),
        io_service(socket->get_io_service()),
        strand_receive(io_service)
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
        stop();
    }

    void TCPConnection::start()
    {
        receive();
        setActive(true);
    }

    void TCPConnection::stop()
    {
        if (!isActive())
            return;
        setActive(false);
        closeSocket();
        std::cout << "CLOSE TCPCON" << std::endl;
    }

    /*
     * Synchronized with the strand.
     */
    void TCPConnection::closeSocket()
    {
        strand_receive.dispatch(boost::bind(&TCPConnection::closeSocketUnsynchronized, this));
    }

    void TCPConnection::stopUnsynchronized()
    {
        if (!isActive())
            return;
        setActive(false);
        closeSocketUnsynchronized();
        std::cout << "CLOSE TCPCON" << std::endl;
    }

    /*
     * Not synchronized with the strand, because this is called
     * from inside the handler. Strand could cause a deadlock.
     */
    void TCPConnection::closeSocketUnsynchronized()
    {
        try {
            if (socket->is_open()) {
                std::cout << this->localPort << " close socket" << std::endl;
                socket->cancel();
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

    void TCPConnection::receive()
    {
        try {
            boost::asio::async_read_until(*socket, receive_buf, '\n',
                                          strand_receive.wrap(
                                              boost::bind(
                                                  &TCPConnection::receiveHandler,
                                                  this,
                                                  boost::asio::placeholders::error,
                                                  shared_from_this()
                                              )));
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    void TCPConnection::receiveHandler(
        const boost::system::error_code& e,
        std::shared_ptr<TCPConnection> c)
    {
        if (!e) {
            std::cout << this->localPort << " Receive Message" << std::endl;

            std::istream is(&receive_buf);
            std::string line;
            std::getline(is, line);

            std::unique_ptr<TCPMessage> msg(new TCPMessage);
            msg->createMessage(line);

            if (msg->isValid()) {
                lastMessage = std::move(msg);
                notifyObservers();
                // Reset the last message (no observer wanted it)
                lastMessage.reset();
            }

            receive();
        } else {
            std::cerr << "RECEIVE HANDLER " << this->localPort << " " << e.message() << std::endl;

            if (e == boost::asio::error::eof ||
                    e == boost::asio::error::connection_reset) {

                stopUnsynchronized();
                notifyObservers();
            }
        }
    }

// =========================================================================

    void TCPConnection::send(std::string str)
    {
        str += "\n";
        try {
            boost::asio::async_write(*socket, boost::asio::buffer(str),
                                     boost::bind(
                                         &TCPConnection::sendHandler,
                                         this,
                                         boost::asio::placeholders::error,
                                         shared_from_this()
                                     ));
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    void TCPConnection::sendHandler(
        const boost::system::error_code& e,
        std::shared_ptr<TCPConnection> c)
    {
        // Nothing to do
    }

    void TCPConnection::sendMessage(TCPMessage& msg)
    {
        send(msg.getFrameData());
    }

}
