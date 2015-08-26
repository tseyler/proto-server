

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

}