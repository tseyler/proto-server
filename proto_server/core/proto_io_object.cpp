

#include <core/proto_io_object.hpp>

using namespace boost::asio::ip;

namespace proto_net {

    template<typename InternetProtocol>
    proto_io_object<InternetProtocol>::proto_io_object() : endpoint_(tcp::v4(), 80),
                                                           acceptor_(io_service_, endpoint_, 80)
    {

    }

    template<typename InternetProtocol>
    proto_io_object<InternetProtocol>::proto_io_object(InternetProtocol internet_proto,
                                                       unsigned short port_num) : endpoint_(internet_proto, port_num),
                                                                                  acceptor_(io_service_, endpoint_, port_num)
    {

    }

    template<typename InternetProtocol>
    io_service&
    proto_io_object<InternetProtocol>::ps_io_service(void) const
    {
        return io_service_;
    }

    template<typename InternetProtocol>
    basic_endpoint<InternetProtocol>&
    proto_io_object<InternetProtocol>::ps_endpoint(void) const
    {
        return endpoint_;
    }

    template<typename InternetProtocol>
    basic_socket_acceptor<InternetProtocol>&
    proto_io_object<InternetProtocol>::ps_acceptor(void) const
    {
        return acceptor_;
    }

}