#include "NetworkControllerServer.h"

namespace controller
{

    NetworkControllerServer::NetworkControllerServer(std::string port) :
        port(port),
        work(io_service),
        endpoint(tcp::endpoint(tcp::v4(), std::atoi(port.c_str()))),
        acceptor(io_service)
    {
        startThreads();
    }

    NetworkControllerServer::~NetworkControllerServer()
    {
        stopServer();
        stopThreads();
    }

    void NetworkControllerServer::startThreads(int count)
    {
        for (int i = 0; i < count; ++i) {
            threadHandles.push_back(
                boost::thread(
                    boost::bind(&boost::asio::io_service::run, &io_service)));
        }
    }

    void NetworkControllerServer::stopThreads()
    {
        io_service.stop();
        for (auto& i : threadHandles)
            i.join();
        threadHandles.clear();
        io_service.reset();
    }

    void NetworkControllerServer::startServer()
    {
        acceptor.open(endpoint.protocol());
        acceptor.bind(endpoint);
        acceptor.listen();

        accept();
    }

    void NetworkControllerServer::stopServer()
    {
        acceptor.cancel();
        acceptor.close();

        connections.clear();
    }

    std::vector<std::shared_ptr<TCPConnection>>&
            NetworkControllerServer::getConnections()
    {
        return connections;
    }

    void NetworkControllerServer::setExternalTCPConnectionObserver(util::Observer *o)
    {
        obs.push_back(o);
    }

    // =========================================================================

    void NetworkControllerServer::accept()
    {
        socket = std::unique_ptr<tcp::socket>(new tcp::socket(io_service));

        try {
            acceptor.async_accept(*socket, boost::bind(
                                      &NetworkControllerServer::acceptHandler,
                                      this,
                                      boost::asio::placeholders::error,
                                      shared_from_this()));
        } catch (std::exception& e) {
            std::cout << "Error accepting connections: " << e.what() << std::endl;
        }
    }

    void NetworkControllerServer::acceptHandler(
        const boost::system::error_code& e,
        std::shared_ptr<NetworkControllerServer> c)
    {
        if (!e) {
            std::shared_ptr<TCPConnection> con(new TCPConnection(std::move(socket)));

            con->addObserver(this);
            for (auto i : obs)
                con->addObserver(i);

            con->start();
            connections.push_back(std::move(con));

            std::cout << "=> Incoming connection accepted." << std::endl;

            accept();
        } else {
            std::cerr << "ACCEPT HANDLER " << e.message() << std::endl;
        }
    }

    void NetworkControllerServer::notify(util::Subject *sub)
    {
        TCPConnection *con = dynamic_cast<TCPConnection*>(sub);

        // Connection is closed, remove from list.
        if (!con->isActive()) {
            for (auto i = connections.begin(); i != connections.end();) {
                if ((*i).get() == con)
                    i = connections.erase(i);
                else
                    ++i;
            }
        }
    }

}
