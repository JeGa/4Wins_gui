#include "NetworkControllerServer.h"

namespace controller
{

	NetworkControllerServer::NetworkControllerServer(std::string port) :
		port(port),
		acceptor(io_service, tcp::endpoint(tcp::v4(), std::atoi(port.c_str()))),
		work(io_service)
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
		accept();
	}

	void NetworkControllerServer::stopServer()
	{
		acceptor.cancel();
		acceptor.close();

		acceptor.open(boost::asio::ip::tcp::v4());

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

//	void NetworkControllerServer::connectionCleanerThread()
//	{
//		std::cout << "=> Cleaner thread started" << std::endl;
//
//		while (true) {
//			try {
//				boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
//			} catch (boost::thread_interrupted& e) {
//				// Close thread
//				break;
//			}
//
//			// Check if a connection is closed from a client
//
//			boost::unique_lock<boost::mutex> l(cleanerMutex);
//
//			if (!clean)
//				cleanerCond.wait_for(l, boost::chrono::milliseconds(100));
//
//			if (clean) { // Check again because of timed wait
//				// The cond. is true
//
//				// Clean connection
//				std::cout << "=> Cleaning closed connection" << std::endl;
//
//				std::vector<std::shared_ptr<TCPConnection>>::iterator rem;
//				for (rem = connections.begin(); rem < connections.end();
//				rem++) {
//
//					if ((*rem).get() == clean) {
//						connections.erase(rem);
//					}
//				}
//
//				clean = nullptr;
//
//				// Then ext threads can notify this thread
//				waitForCleanedMutex.unlock();
//			}
//		}
//
//		std::cout << "=> Cleaner thread closing" << std::endl;
//	}

	// Notified from the TCPConnection receive thread
	void NetworkControllerServer::notify(util::Subject *sub)
	{
		TCPConnection *con = dynamic_cast<TCPConnection*>(sub);

		// Connection is closed:
//        if (!con->isActive()) {
//            // Remove from list: Notify cleaner thread
//
//            waitForCleanedMutex.lock();
//
//            cleanerMutex.lock();
//            clean = con;
//            cleanerCond.notify_one();
//            cleanerMutex.unlock();
//        }
	}

}
