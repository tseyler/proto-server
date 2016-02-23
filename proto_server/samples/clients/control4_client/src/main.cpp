// main.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <sstream>
#include <core/client/proto_tcp_text_client.hpp>
#include "director_pipeline.hpp"
#include "director.hpp"
#include "cmd_parser.hpp"

//#include <vector>
//#include <boost/thread.hpp>
//#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

using namespace proto_net::data;
using namespace proto_net;
using namespace proto_net::client;

static const std::string ver = "1.0.1";
static const std::string bld_date_time = "2/23/16; 11:10 AM";

void console_func(void*)
{
	bool alive(true);
	std::string console_input;

	while (alive)
	{
		std::getline(std::cin, console_input);
		if (boost::iequals(console_input, "exit"))
			alive = false;
	}

	std::cout << "Exiting..." << std::endl;
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
    std::cerr << out << std::endl;
}

void
print_banner(void)
{
    print_ln("c4-client - A command line tool to send C4SOAP commands to a Control4 controller.");
    print_ln("Version: " + ver);
    print_ln("Built: " + bld_date_time);
    print_ln("Copyright 2016 Terry Seyler.  All rights reserved.");
    print_ln("------------");
}

void
print_usage(void)
{
    std::cout << "Usage:" << std::endl;
    std::cout << "$ c4-client <host> <command> [id] [param1] [param2] ..." << std::endl;
}

//bool
//print_shell(cmd_parser& parser, bool in_shell)
//{
//    if (in_shell)
//    {
//        char shell[256];
//        std::cout << std::endl << ">> ";
//        std::cin.getline(shell, 256);
//        in_shell = parser.parse(std::string(shell));
//    }
//
//    return in_shell;
//}

void
print_verbose(const std::string& msg)
{
    print_ln("<<--Out-->>");
    print_ln(msg);
    print_ln("<<--End Out-->>");
}

char**
get_args(char* argv[], int first_arg)
{
    return &argv[first_arg];
}

int 
main(int argc, char* argv[])
{
    bool silent(false);
    bool is_shell(false);
    bool is_verbose(false);
    int first_arg(1);

    po::options_description desc("Options");
    desc.add_options()
            ("help,h", "Prints the help message")
            ("silent,s", "Suppresses the copyright banner")
            ("interactive,i", "Executes as an interactive shell")
            ("verbose,v", "Prints outgoing messages as well as incoming responses");

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

        if (vm.count("verbose"))
        {
            is_verbose = true;
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
        //print_error(e.what());
        std::cerr << desc << std::endl;
        return 1;
    }

    if (argc > 0)
    {
        char **args = get_args(argv, first_arg);
        cmd_parser parser(args, argc);
        std::string host = parser.host();
        std::string cmd = parser.cmd();
        // authenticate

        int seq(1);
        std::string msg = parser.to_authenticate(seq);

        // create a pipeline for the client
        director_pipeline dir_pipeline(host);
        // create the client
        proto_tcp_text_client dir_client(host, 5020, dir_pipeline);

        // authenticate c4soap message for director to allow a connection
        proto_net_in_data cmd_data(msg);
        // connect to the downstream server (director)
        dir_client.ps_async_connect(cmd_data);
        // start the client service
        dir_client.ps_start();

        void *dummy(NULL);
        boost::thread console_thd(console_func, dummy);

        console_thd.join();

        dir_client.ps_stop();

        std::cout << "Done." << std::endl;
    }

    ////////////////////////////////////////

//
//
//        // authenticate
//        int seq(1);
//        std::string msg = parser.to_authenticate(seq);
//        c4socket::write_msg(s, msg);
//        std::string reply = c4socket::read_msg(s);
//        print_ln(reply);
//
//        do
//        {
//            msg = parser.to_c4soap(seq);
//            cmd = parser.cmd();
//            if (parser.parsed())
//            {
//                if (is_verbose)
//                    print_verbose(msg);
//                c4socket::write_msg(s, msg);
//                reply = c4socket::read_msg(s);
//                print_ln(reply);
//            }
//            else
//                print_ln("Unknown or malformed command: " + cmd);
//            is_shell = print_shell(parser, is_shell);
//        }
//        while (is_shell);
//    }
//    else
//        print_usage();

    ////////////////////////////////
    return 0;
}

