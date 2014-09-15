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

static const std::string ver = "1.0.5";
static const std::string bld_date_time = "9/15/14; 4:05 PM";

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
print_banner(void)
{
	print_ln("c4-console - A command line tool to send C4SOAP commands to a Control4 controller.");
	print_ln("Version: " + ver);
	print_ln("Built: " + bld_date_time);
	print_ln("(c) Terry Seyler 2014.  All rights reserved.");
	print_ln("------------");
}

void 
print_usage(void)
{
    std::cout << "Usage:" << std::endl;
    std::cout << "$ c4-console <host> <command> [id] [param1] [param2] ..." << std::endl;
}

bool
print_shell(cmd_parser& parser, bool in_shell)
{
	if (in_shell)
	{
		char shell[256];
		std::cout << std::endl << ">> ";
		std::cin.getline(shell, 256);
		in_shell = parser.parse(std::string(shell));
	}

	return in_shell;
}

char**
get_args(char* argv[], int first_arg)
{
    return &argv[first_arg];
}

int 
main(int argc, 
	char *argv[])
{
	bool silent(false);
	bool is_shell(false);
	int first_arg(1);

	po::options_description desc("Options");
	desc.add_options()
		("help,h", "Prints the help message")
		("silent,s", "Suppresses the copyright banner")
		("interactive,i", "Executes as an interactive shell");

	po::variables_map vm;
	try
	{
		po::store(po::parse_command_line(argc--, argv, desc), vm);


		if (vm.count("silent"))
		{
			silent = true;
			argc--;
			first_arg++;
		}

		if (!silent) 
			print_banner();

		if (vm.count("interactive"))
		{
			is_shell = true;
			argc--;
			first_arg++;
		}

		if (vm.count("help"))
		{
			print_usage();
			return 0;
		}
	}
	catch (po::error& e)
	{


	}
	
    if (argc > 1)
    {
		char** args = get_args(argv, first_arg);
		cmd_parser parser(args, argc);
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

		do
		{
			msg = parser.to_c4soap(seq);
			cmd = parser.cmd();
			if (parser.parsed())
			{
				c4socket::write_msg(s, msg);
				reply = c4socket::read_msg(s);
				print_ln(reply);
			}
			else
				print_ln("Unknown or malformed command: " + cmd);
			is_shell = print_shell(parser, is_shell);
		}
		while (is_shell);
	}
	else
		print_usage();

	return 0;
}

