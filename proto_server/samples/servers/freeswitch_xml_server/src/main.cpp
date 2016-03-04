
#include <boost/algorithm/string.hpp>
#include "freeswitch_xml_pipeline.hpp"
//#include <core/proto_service.hpp>
#include <core/factory/proto_tcp_server_factory.hpp>

using namespace proto_net;
using namespace proto_net::factory;

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

int
main(int argc, char *argv[])
{
    std::string server_address("127.0.0.1");

    freeswitch_xml_pipeline fs_pipeline;
    proto_tcp_server_factory server_factory(fs_pipeline, 8095);
    proto_service_ptr fs_server = server_factory();


    void* dummy(NULL);
    boost::thread console_thd(console_func, dummy);

    console_thd.join();

    fs_server->ps_stop();

    std::cout << "Done." << std::endl;

    return 0;
}