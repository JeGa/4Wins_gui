#include "TCPConnection.h"
#include <iostream>
#include <boost/chrono.hpp>

namespace controller
{

    const int TCPConnection::KEEP_ALIVE_TIME_SEND_SECONDS = 10;
    const int TCPConnection::KEEP_ALIVE_TIME_CHECK_SECONDS = 2;

    TCPConnection::TCPConnection(std::unique_ptr<tcp::socket> s) :
        socket(std::move(s)),
        io_service(socket->get_io_service()),
        checkKeepAliveTimer(io_service,
                            boost::posix_time::seconds(KEEP_ALIVE_TIME_CHECK_SECONDS)),
        sendKeepAliveTimer(io_service,
                           boost::posix_time::seconds(KEEP_ALIVE_TIME_SEND_SECONDS)),
        strand_receive(io_service),
        strand_checkKeepAlive(io_service),
        strand_sendKeepAlive(io_service)
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
//        checkKeepAlive();
//        sendKeepAlive();

        setKeepAlive();

        setActive(true);
    }

    void TCPConnection::stop()
    {
        if (!isActive())
            return;
        setActive(false);
        closeSocket();
        closeWaits();
        std::cout << "CLOSE TCPCON" << std::endl;
    }

    void TCPConnection::closeSocket()
    {
        strand_receive.dispatch([this]() {
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
        });
    }

    void TCPConnection::closeWaits()
    {
        std::cout << this->localPort << " close waits" << std::endl;
        strand_sendKeepAlive.dispatch([this]() {
            checkKeepAliveTimer.cancel();
        });
        strand_checkKeepAlive.dispatch([this]() {
            sendKeepAliveTimer.cancel();
        });
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
                if (!parseMessageInternal(*msg)) {
                    lastMessage = std::move(msg);
                    notifyObservers();
                    // Reset the last message (no observer wanted it)
                    lastMessage.reset();
                }
            }

            receive();
        } else {
            std::cerr << "RECEIVE HANDLER " << this->localPort << " " << e.message() << std::endl;

            if (e == boost::asio::error::eof ||
                    e == boost::asio::error::connection_reset) {

                if (isActive()) {
                    std::cout << this->localPort << " close from handler" << std::endl;
                    setActive(false);
                    try {
                        if (socket->is_open()) {
                            std::cout << this->localPort << " close socket" << std::endl;
                            socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
                            socket->close();
                        }
                    } catch (std::exception& e) {
                        std::cerr << e.what() << std::endl;
                    }
                    closeWaits();
                }
                notifyObservers();
            }
        }
    }

    void TCPConnection::checkKeepAlive()
    {
        checkKeepAliveTimer.async_wait(strand_checkKeepAlive.wrap(
                                           boost::bind(
                                               &TCPConnection::checkKeepAliveHandler,
                                               this,
                                               boost::asio::placeholders::error,
                                               shared_from_this()
                                           )));
    }

    void TCPConnection::checkKeepAliveHandler(
        const boost::system::error_code& e,
        std::shared_ptr<TCPConnection> c)
    {
        std::cout << this->localPort << " Check Keep Alive" << std::endl;

        if (!e) {
            boost::chrono::steady_clock::time_point now =
                boost::chrono::steady_clock::now();
            auto d = now - lastKeepAlive;

            if (d >= boost::chrono::seconds(KEEP_ALIVE_TIME_SEND_SECONDS + 5)) {
                // No keep alive after x seconds: Client closed the socket
//                if (isActive()) {
//                    closeSocket();
//                    checkKeepAliveTimer.cancel();
//                    sendKeepAliveTimer.cancel();
//                }
//                notifyObservers();
            }

            checkKeepAliveTimer.expires_at(checkKeepAliveTimer.expires_at() +
                                           boost::posix_time::seconds(KEEP_ALIVE_TIME_CHECK_SECONDS));

            checkKeepAlive();
        } else {
            std::cerr << "CHECKKA: " <<this->localPort << " " << e.message() << std::endl;

            if (e == boost::asio::error::eof ||
                    e == boost::asio::error::connection_reset) {

//                if (isActive()) {
//                    std::cout << this->localPort << " close from handler" << std::endl;
//                    setActive(false);
//                    closeSocket();
//                    checkKeepAliveTimer.cancel();
//                    strand_sendKeepAlive.dispatch([this]() {
//                        checkKeepAliveTimer.cancel();
//                    });
//                }
//                notifyObservers();
            }
        }
    }

    void TCPConnection::sendKeepAlive()
    {
        sendKeepAliveTimer.async_wait(strand_sendKeepAlive.wrap(
                                          boost::bind(
                                              &TCPConnection::sendKeepAliveHandler,
                                              this,
                                              boost::asio::placeholders::error,
                                              shared_from_this()
                                          )));
    }

    void TCPConnection::sendKeepAliveHandler(
        const boost::system::error_code& e,
        std::shared_ptr<TCPConnection> c)
    {
        std::cout << this->localPort << " Send Keep Alive" << std::endl;

        if (!e) {
            TCPMessage msg;
            msg.createKeepAliveMessage();
            sendMessage(msg); // TODO ??

            sendKeepAliveTimer.expires_at(sendKeepAliveTimer.expires_at() +
                                          boost::posix_time::seconds(KEEP_ALIVE_TIME_SEND_SECONDS));

            sendKeepAlive();
        } else {
            std::cerr << "SENDKA: " <<this->localPort << " " << e.message() << std::endl;

            if (e == boost::asio::error::eof ||
                    e == boost::asio::error::connection_reset) {

//                if (isActive()) {
//                    std::cout << this->localPort << " close from handler" << std::endl;
//                    setActive(false);
//                    closeSocket();
//                    strand_checkKeepAlive.dispatch([this]() {
//                        sendKeepAliveTimer.cancel();
//                    });
//                    sendKeepAliveTimer.cancel();
//                }
//                notifyObservers();
            }
        }
    }

// =========================================================================

// Blocking TODO: Synchronize, change to async send.

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
