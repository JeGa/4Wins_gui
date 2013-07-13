#ifndef SERVERNETWORKCONTROLLER_H
#define SERVERNETWORKCONTROLLER_H

#include <boost/asio.hpp>

namespace controller
{

    class ServerNetworkController
    {
    private:
        boost::asio::io_service io_service;
        int port = 9999;
        
    public:
        ServerNetworkController();
        virtual ~ServerNetworkController();
        
        void startServer();

    };

}

#endif // SERVERNETWORKCONTROLLER_H
