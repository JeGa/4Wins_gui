//#ifndef SERVERNETWORKCONTROLLER_H
//#define SERVERNETWORKCONTROLLER_H
//
//// MinGW/Boost/Python problem
//#undef hypot
//
//#include <cmath>
//#include <ctime>
//#include <iostream>
//#include <string>
//#include <boost/asio.hpp>
//
//namespace controller
//{
//	
//	using boost::asio::ip::tcp;
//	
//    class ServerNetworkController
//    {
//    private:
//        boost::asio::io_service io_service;
//		tcp::socket socket;
//		
//        int port = 9999;
//        
//		void handle_accept(
//			const boost::system::error_code& error);
//		void handle_write(
//			const boost::system::error_code& error,
//			std::size_t bytes_transferred);
//    public:
//        ServerNetworkController();
//        virtual ~ServerNetworkController();
//        
//        void startServer();
//
//    };
//
//}
//
//#endif // SERVERNETWORKCONTROLLER_H
