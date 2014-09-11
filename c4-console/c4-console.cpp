// c4-console.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>

#include "director.hpp"
#include "c4socket.hpp"
#include "cmd_parser.hpp"

#define THROW_BOOST_ERROR( e ) if (e.value() > 0) throw e

namespace po = boost::program_options;
using boost::asio::ip::tcp;

static const std::string ver = "1.0.1";

void
print_banner(void)
{
	std::cout << "c4-console - Version: " << ver << std::endl;
	std::cout << "© Terry Seyler 2013.  All rights reserved." << std::endl;
	std::cout << "------------" << std::endl;
}

void 
print_usage(void)
{
    std::cout << "Usage:" << std::endl;
    std::cout << "$ c4-console <host> <command> [id] [param1] [param2] ..." << std::endl;
}

void 
print(const std::string& out)
{
    std::cout << out;
}

void 
print_ln(const std::string& out)
{
    print(out);
    std::cout << std::endl;
}

void
print_error(const std::string& err)
{
	std::string out = "ERROR: " + err;
	print_ln(out);
}

char**
get_args(char* argv[])
{
    return &argv[1];
}

int 
main(int argc, 
	char *argv[])
{
	print_banner();
	
    if (argc > 1)
    {
		char** args = get_args(argv);
		cmd_parser parser(args, --argc);
		std::string host = parser.host();
		std::string cmd = parser.cmd();

		boost::system::error_code ec;
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(host.c_str(), "5020");
		tcp::resolver::iterator iterator;
		try
		{
			iterator = resolver.resolve(query, ec);
			THROW_BOOST_ERROR( ec );
		}
		catch (boost::system::error_code& e)
		{
			print_error(e.message());
			return e.value();
		}
		
		tcp::socket s(io_service);
		try
		{
			tcp::endpoint ep = *iterator;
			s.connect(ep, ec);
			THROW_BOOST_ERROR( ec );
		}
		catch (boost::system::error_code& e)
		{
			print_error(e.message());
			return e.value();
		}


		// authenticate
		int seq(1);
		std::string msg = parser.to_authenticate(seq);
		c4socket::write_msg(s, msg);
		std::string reply = c4socket::read_msg(s);
		print_ln(reply);

		msg = parser.to_c4soap(seq);
		if (parser.parsed())
		{
			c4socket::write_msg(s, msg);
			reply = c4socket::read_msg(s);
			print_ln(reply);
		}
		else
			print_ln("Unknown or malformed command: " + cmd);
	}
	else
		print_usage();

	return 0;
}

