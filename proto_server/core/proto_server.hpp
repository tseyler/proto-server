//
// Created by Terry Seyler on 8/19/15.
//

#ifndef PROTO_SERVER_HPP__
#define PROTO_SERVER_HPP__

# include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include <core/proto_constants.h>
#include <core/proto_io_object.hpp>

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

namespace proto_net
{

    template <typename InternetProtocol>
    class proto_server
    {
    public:

        typedef shared_ptr<proto_io_object<InternetProtocol> > Proto_IO_Object;

        proto_server();
        proto_server(int protocol_family, unsigned short port_num);
        // copy constructor
        proto_server(const proto_server& ps);

        virtual ~proto_server() {}

        proto_server& clone(const proto_server& ps);

        proto_server& operator =(const proto_server& ps);

        // pure virtuals
        virtual void ps_initialize(void) = 0;
        virtual void ps_run(void) = 0;

        // getters
        Proto_IO_Object& ps_io_object(void) const;
        int ps_af_protocol_family(void) const;
        unsigned short ps_port_number(void) const;

    protected:

        virtual void ps_start_accept(void) = 0;

    protected:

        Proto_IO_Object io_object_;
        int af_protocol_family_;
        unsigned short port_num_;
    };
}

#endif //PROTO_SERVER_HPP__

