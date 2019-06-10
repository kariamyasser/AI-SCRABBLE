//
// communication_server.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Synchronous (blocking) server for game engine, supports connecting 1 client only
//
// Compile with C++11
//
// Check README.txt file for instructions and documentation
//
//
//

#pragma once

#ifndef _SERVER_HPP
#define _SERVER_HPP

//Remove boost dependency (Requires C++11)
#define ASIO_STANDALONE

//For Windows SDK, Target Windows 7 
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif // !_WIN32_WINNT


#endif // defined(WIN32) || defined(_WIN32) || defined(__WIN32__)


#include <string>
#include <queue>
#include <iostream>
#include <cstdint>
#include "communication\asio.hpp"
#define comm asio::ip

namespace communication
{


	class server
	{
		asio::io_service io_service;
		comm::tcp::acceptor _acceptor;
		comm::tcp::socket _socket;
		enum { buffer_size = 128 };
		char receive_buffer[buffer_size];
		char send_buffer[buffer_size];
		std::queue<std::string> message_queue;


	public:
		//Constructor
		//port: Port to bind server with. make sure that port specified is not already bound with another application
		server(short port)
			: _acceptor(io_service, comm::tcp::endpoint(comm::tcp::v4(), port)), _socket(io_service)
		{

		}

		//Destructor
		~server()
		{

		}

		//Starts the server and waits in blocking mode for the client to connect 
		void start()
		{
			std::cout << "Waiting for gui to connect...\n";
			_acceptor.accept(_socket);	//accept 1 client
			_acceptor.close();	//close the acceptor. stops accepting any other client
			_socket.set_option(comm::tcp::no_delay(true)); //Disable Nagle's algorithm
			_socket.set_option(comm::tcp::socket::receive_buffer_size(5 * buffer_size));
		}

		//Sends a message to GUI
		//message: message to send
		//return: return true if the message was send successfully
		bool send_message(std::string message)
		{
			std::cout << "Sending message to GUI\n";
			for (int i = 0; i < message.length(); i++)
			{
				send_buffer[i] = message[i];
			}

			bool success = this->send(message.length()); //Send 5 bytes

			return success;
		}

		bool isConnected()
		{
			return this->_socket.is_open();
		}

		//Waits till a message is received
		std::string receive()
		{
			asio::error_code error;

			std::cout << "Waiting for a message from GUI...\n";
			std::size_t length = _socket.read_some(asio::buffer(receive_buffer, buffer_size), error);
			if (error)
			{
				std::cout << "Error in communication...\n";
			}
			std::cout << "Received a message from GUI: " << std::string(receive_buffer, length) << '\n';
			return std::string(receive_buffer, length);
		}

	private:

		//Synchronous send
		bool send(std::size_t length)
		{
			asio::error_code error;
			_socket.write_some(asio::buffer(send_buffer, length), error);
			return !error;
		}

	};
}

#endif // !_SERVER_HPP


