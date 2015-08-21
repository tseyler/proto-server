//
// Created by Terry Seyler on 8/19/15.
//

#ifndef PROTO_SERVER_HPP__
#define PROTO_SERVER_HPP__

#include <boost/asio.hpp>

#include <core/proto_constants.h>

using namespace boost::asio;
using namespace boost::asio::ip;

namespace proto_net
{
    template <typename InternetProtocol>
    class proto_server
    {
    public:

        proto_server();
        proto_server(int protocol_family, unsigned short port_num);
        // copy constructor
        proto_server(const proto_server& ps);

        virtual ~proto_server() {}

        proto_server& clone(const proto_server& ps);

        proto_server& operator =(const proto_server& ps);

        // pure virtual
        virtual InternetProtocol ps_internet_protocol(void) const = 0;

        // getters
        int ps_af_protocol_family(void) const;
        unsigned short ps_port_number(void) const;
        basic_endpoint<InternetProtocol> ps_endpoint(void) const;

    protected:

        int af_protocol_family_;
        unsigned short port_num_;
        basic_endpoint<InternetProtocol> endpoint_;
        io_service io_service_;

    };
}

#endif //PROTO_SERVER_HPP__

