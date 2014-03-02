#include "NetworkControllerClient.h"

namespace controller
{

    NetworkControllerClient::NetworkControllerClient(std::string addr, std::string port)
        : address(addr), port(port), work(io_service)
    {
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(address, port);

        // DNS resolve
        endpoint_iterator = resolver.resolve(query);

        startThreads();
    }

    NetworkControllerClient::~NetworkControllerClient()
    {
        stopThreads();
        disconnect();
    }

    void NetworkControllerClient::startThreads(int count)
    {
        for (int i = 0; i < count; ++i) {
            threadHandles.push_back(
                boost::thread(
                    boost::bind(&boost::asio::io_service::run, &io_service)));
        }
    }

    void NetworkControllerClient::stopThreads()
    {
        io_service.stop();
        for (auto& i : threadHandles)
            i.join();
        threadHandles.clear();
        io_service.reset();
    }

    void NetworkControllerClient::disconnect()
    {
        // TODO: Cancel all io service events ?
        con->stop();
        con.reset();
    }

    // TODO
    bool NetworkControllerClient::ping()
    {
        return false;

        if (isConnected())
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
        con = std::shared_ptr<TCPConnection>(
                  new TCPConnection(std::move(clientCon)));

        for (auto i : obs)
            con->addObserver(i);

        con->start();
        std::cout << "Client: Connected" << std::endl;
    }

    void NetworkControllerClient::send(TCPMessage& msg)
    {
//        con->sendMessage(msg);
    }

    void NetworkControllerClient::setExternalTCPConnectionObserver(util::Observer *o)
    {
        obs.push_back(o);
    }

    bool NetworkControllerClient::isConnected()
    {
        return (con ? true : false);
    }

}
