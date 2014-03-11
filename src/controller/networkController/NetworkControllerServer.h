#ifndef SERVERNETWORKCONTROLLER_H
#define SERVERNETWORKCONTROLLER_H

// MinGW/Boost/Python problem
#undef hypot

#include "TCPConnection.h"
#include "Observer.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <vector>

namespace controller
{

	using boost::asio::ip::tcp;

	class NetworkControllerServer :
		public util::Observer,
		public std::enable_shared_from_this<NetworkControllerServer>
	{
		private:
			boost::asio::io_service io_service;
			boost::asio::io_service::work work;

			std::vector<boost::thread> threadHandles;

			tcp::acceptor acceptor;
			std::string port;

			boost::thread acceptorThreadHandle;
			boost::thread cleanerThreadHandle;

			boost::condition_variable cleanerCond;
			boost::mutex cleanerMutex;
			boost::mutex waitForCleanedMutex;
			TCPConnection *clean = nullptr;

			/*
			 * Holds all client connections
			 */
			std::vector<std::shared_ptr<TCPConnection>> connections;

			/*
			 * Observers to set for the TCPConnection.
			 * Be careful with the mm here.
			 */
			std::vector<util::Observer*> obs;

			std::unique_ptr<tcp::socket> socket;

			void accept();
			void acceptHandler(
			    const boost::system::error_code& e,
			    std::shared_ptr<NetworkControllerServer> c);

			void startThreads(int count = 1);
			void stopThreads();

		public:
			NetworkControllerServer(std::string port = "9999");
			virtual ~NetworkControllerServer();

			void setExternalTCPConnectionObserver(util::Observer *o);

			void startServer();
			void stopServer();
			std::vector<std::shared_ptr<TCPConnection>>& getConnections();

			virtual void notify(util::Subject *sub);
	};

}

#endif // SERVERNETWORKCONTROLLER_H
