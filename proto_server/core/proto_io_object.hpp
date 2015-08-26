//
// Created by Terry Seyler on 8/21/15.
//

#ifndef PROTO_IO_OBJECT_HPP__
#define PROTO_IO_OBJECT_HPP__

#include <boost/asio.hpp>

#include <core/proto_constants.h>

using namespace boost::asio;
using namespace boost::asio::ip;

namespace proto_net
{
    template <typename InternetProtocol>
    class proto_io_object
    {
    public:

        proto_io_object();
        proto_io_object(InternetProtocol internet_proto, unsigned short port_num);
        virtual ~proto_io_object() {}

        // getters



    protected:

        io_service io_service_;
        basic_endpoint<InternetProtocol> endpoint_;
        basic_socket_acceptor<InternetProtocol> acceptor_;
    };

}

#endif

