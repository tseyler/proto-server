//
// Created by Terry Seyler on 8/19/15.
//

#ifndef PROTO_SERVER_HPP__
#define PROTO_SERVER_HPP__

#include <boost/asio.hpp>

#include <core/proto_constants.h>

namespace proto_net
{
    template <typename InternetProtocol>
    class proto_server
    {
    public:

        proto_server() {}
        virtual ~proto_server() {}

    protected:

        boost::asio::io_service io_service_;
        boost::asio::ip::basic_endpoint<InternetProtocol> endpoint_;
    };
}

#endif //PROTO_SERVER_HPP__

