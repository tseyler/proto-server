

#include "proto_echo_server_pipeline.hpp"
#include "proto_echo_client_pipeline.hpp"

#include <core/factory/proto_tcp_text_client_factory.hpp>
#include <core/factory/proto_tcp_text_server_factory.hpp>

//using namespace proto_net::server;
//using namespace proto_net::client;
using namespace proto_net::factory;

int
main(int argc, char *argv[])
{
    std::string echo_server_address("127.0.0.1");

    // echo server
    proto_echo_server_pipeline echo_server_pipeline;
    proto_tcp_text_server_factory server_factory(echo_server_pipeline, 9669);
    proto_service_ptr echo_server = server_factory();

    // echo client
    proto_echo_client_pipeline echo_client_pipeline;
    proto_net_in_data echo_data("Hello World!"); // our first message once we connect
    proto_tcp_text_client_factory client_factory(echo_server_address, echo_data, 9669, echo_client_pipeline);
    proto_service_ptr echo_client = client_factory();

    proto_net_in_data another_data("Another Hello World!");
    proto_async_io* async_writer = proto_tcp_text_client::proto_async_io_cast(echo_client);
    async_writer->ps_async_write(another_data);
    proto_tcp_text_client* client_ptr = proto_tcp_text_client::proto_tcp_text_client_cast(echo_client);
    // wait for last write to complete before stopping
    client_ptr->ps_write_complete(250); // 1/4 sec

    echo_client->ps_stop();
    echo_server->ps_stop();

    std::cout << "Done." << std::endl;

    return 0;
}