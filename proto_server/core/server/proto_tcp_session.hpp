//
// Created by Terry Seyler on 8/30/15.
//

#ifndef PROTO_TCP_SESSION_HPP__
#define PROTO_TCP_SESSION_HPP__

#include <core/proto_io_tcp_object.hpp>
#include <core/server/proto_session.hpp>

using namespace boost::asio::ip;
using namespace proto_net::data;

namespace proto_net
{
    namespace server
    {
        class proto_tcp_session : public proto_session
        {
        public:

            proto_tcp_session(proto_net_io& ps_io, unsigned short port_num = 80, size_t buffer_size = 4096);
            virtual ~proto_tcp_session();

            virtual void start(void);
            virtual void read(void);
            virtual void write(const char* data, size_t data_size);

            virtual void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
            virtual void handle_write(const boost::system::error_code& error);

            // getter
            tcp::socket& ps_socket(void);

        protected:

            proto_io_tcp_object tcp_io_object_;
            tcp::socket socket_;
        };
    }

}

#endif
