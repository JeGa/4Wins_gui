//#include "ServerNetworkController.h"
//#include <iostream>
//
//namespace controller
//{
//
//    ServerNetworkController::ServerNetworkController()
//    {
//    }
//
//    ServerNetworkController::~ServerNetworkController()
//    {
//    }
//	
//	void ServerNetworkController::handle_write(
//		const boost::system::error_code& error,
//		std::size_t bytes_transferred)
//	{
//		std::cout << "Wite handle" << std::endl;
//	}
//	
//	void ServerNetworkController::handle_accept(
//		const boost::system::error_code& error)
//	{
//		std::string s = "Hi from server.";
//		
//		std::cout << "Accept handle" << std::endl;
//		boost::asio::async_write(socket, boost::asio::buffer(s), handle_write);
//	}
//    
//    void ServerNetworkController::startServer()
//    {
////        try {
//            
//            tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));
//        
//			tcp::socket socket(io_service);
//		
////			for (;;) {
//		
////			tcp_connection::pointer new_connection = tcp_connection::create(io_service);
//			
//
//			acceptor.async_accept(socket, handle_accept);
//		
//		
//			io_service.run();
//		
////            for (;;) {
////                tcp::socket socket(io_service);
////                
////				std::cout << "Waiting for incoming connections" << std::endl;
////				
////                acceptor.accept(socket);
////				
////				std::cout << "Waiting for incoming connections" << std::endl;
////
////                std::string message = "Hello here is the server";
////
////                boost::system::error_code ignored_error;
////                boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
////            }
////            
////        } catch (std::exception& e) {
////            std::cerr << e.what() << std::endl;
////        }
//        
//    }
//
//}
//
