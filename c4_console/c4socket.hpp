

#ifndef C4SOCKET_HPP__
#define C4SOCKET_HPP__

#include <iostream>
#include <string.h>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

#define BUFFER_SIZE 4096

namespace c4socket
{

	// write a message to the socket
	size_t write_msg(tcp::socket& s, const std::string& msg);

	// read a message off the socket
	std::string read_msg(tcp::socket& s);
}

#endif