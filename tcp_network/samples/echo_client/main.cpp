/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/


#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>


#define THROW_BOOST_ERROR( e ) if (e.value() > 0) throw e

#define BUFFER_SIZE 4096

namespace po = boost::program_options;
using boost::asio::ip::tcp;

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

void 
print_usage(void)
{
    std::cout << "Usage:" << std::endl;
    std::cout << "$ c4-console <host> <command> [id] [param1] [param2] ..." << std::endl;
}

char**
get_args(char* argv[], int first_arg)
{
    return &argv[first_arg];
}

size_t 
write_msg(tcp::socket& s, const std::string& msg)
{
    char buf[BUFFER_SIZE];
    memset(buf, 0, BUFFER_SIZE);
    memcpy(buf, msg.c_str(), msg.length());
 
    return boost::asio::write(s, boost::asio::buffer(buf, strlen(buf) + 1));
}

std::string 
read_msg(tcp::socket& s)
{
    char buf[BUFFER_SIZE];
    memset(buf, 0, BUFFER_SIZE);
    boost::asio::streambuf b;
    if (boost::asio::read_until(s, b, '\0'))
    {
		std::istream is(&b);
		is.get(buf, BUFFER_SIZE, '\0');
    }

    return std::string(buf);
}

int 
main(int argc, char* argv[])
{
	int first_arg(1);

	po::options_description desc("Options");
	desc.add_options()
		("help,h", "Prints the help message");

	po::variables_map vm;
	try
	{
		po::store(po::parse_command_line(argc--, argv, desc), vm);

		if (vm.count("help"))
		{
			print_usage();
			return 0;
		}
	}
	catch (po::error& e)
	{


	}
	
    //if (argc > 1)
    //{
		char** args = get_args(argv, first_arg);
		std::string echo_server = "127.0.0.1"; // std::string(args[0]);
		std::string echo_string = "Hello World!"; // std::string(args[1]);
		
		boost::system::error_code ec;
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(echo_server.c_str(), "9669");
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
		
		// write the message to be echoed
		write_msg(s, echo_string);
		// read it back
		std::string reply = read_msg(s);

		print_ln(reply);
	//}
	//else
		//print_usage();

	return 0;
}

