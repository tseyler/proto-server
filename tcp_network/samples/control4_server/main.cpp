/*
<boilerplate>



</boilerplate>
*/

#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include "control4_server.hpp"

const static std::string ver = "0.0.1";

// boost
namespace po = boost::program_options;

void
printHelp(const po::options_description& desc)
{
    std::cout << desc << std::endl;
}

void
printVersion(void)
{
    std::cout << "Control4 Server: " << ver << std::endl;
}

void printStartup(short port)
{
    std::cout << "Starting Control4 Server " << ver << " on port " << port << " ..." << std::endl;
}

int main(int argc, char *argv[])
{  
    short port(5020);

    po::options_description desc("Allowed options");
    desc.add_options()
	("help,h", "produce help message")
	("version,v", "returns the version")
	("port,p", po::value<short>(&port)->default_value(5020), 
	 "TCP port that the server is listening on")
        ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);

    if (vm.count("help"))
    {
	printHelp(desc);
	return 1;
    }
    if (vm.count("version"))
    {
	printVersion();
	return 1;
    }
    if (vm.count("port"))
	port = vm["port"].as<short>();

    printStartup(port);

    boost::asio::io_service io_service;
    control4::control4_server server(io_service, port);
    server.run();

    return 0;
}

