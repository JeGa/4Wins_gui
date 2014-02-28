#include "NetworkControllerClient.h"

namespace controller
{

    NetworkControllerClient::NetworkControllerClient(std::string addr, std::string port)
        : address(addr), port(port)
    {
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(address, port);

        // DNS resolve
        endpoint_iterator = resolver.resolve(query);
    }

    NetworkControllerClient::~NetworkControllerClient()
    {
        disconnect();
    }

    bool NetworkControllerClient::ping()
    {
        if (this->isConnected())
            return true;

        connect();

        // If error connecting to server
        if (!con)
            return false;
        else
            disconnect();

        return true;
    }

    void NetworkControllerClient::connect()
    {
        disconnect();

        try {
            std::unique_ptr<tcp::socket> clientCon(
                new tcp::socket(io_service));

            boost::asio::connect(*clientCon, endpoint_iterator);

            startTCPConnection(std::move(clientCon));

        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void NetworkControllerClient::startTCPConnection(
        std::unique_ptr<tcp::socket> clientCon)
    {
        // Move ownership to TCPConnection
        con = std::unique_ptr<TCPConnection>(
                  new TCPConnection(std::move(clientCon)));

        for (auto i : obs)
            con->addObserver(i);

        con->startConnectionThread();

        std::cout << "Client: Connected" << std::endl;
    }

    void NetworkControllerClient::disconnect()
    {
        if (con) {
            con.release();
        }
    }

    void NetworkControllerClient::send(TCPMessage& msg)
    {
        con->sendMessage(msg);
    }

    void NetworkControllerClient::setExternalTCPConnectionObserver(util::Observer *o)
    {
        obs.push_back(o);
    }

    bool NetworkControllerClient::isConnected()
    {
        if (con)
            return true;
        return false;
    }

}
