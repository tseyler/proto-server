//
//  proto_tcp_session.hpp - base class for tcp server sessions
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef PROTO_TCP_SESSION_HPP_
#define PROTO_TCP_SESSION_HPP_

#include <core/proto_net_types.hpp>
#include <core/proto_async_io.hpp>
#include <core/server/proto_session.hpp>

using namespace boost::asio::ip;
using namespace proto_net::data;

namespace proto_net
{
    namespace server
    {
        class proto_tcp_session : public proto_async_io, public proto_session
        {
        public:

            proto_tcp_session(proto_net_service_ptr ps_service, proto_net_pipeline& ps_pipeline,
                             size_t buffer_size = 4096);
            virtual ~proto_tcp_session();

            virtual void ps_start(void);
            virtual void ps_async_read(void);
            virtual void ps_async_write(proto_net_out_data& data_out, bool no_write_complete = false);
            virtual proto_net_pipeline& ps_pipeline(void);

            virtual void ps_handle_read(const boost::system::error_code &error, size_t bytes_transferred);
            virtual void ps_handle_write(const boost::system::error_code &error);

            virtual bool ps_read_complete(size_t max_wait_msec = 2000);

            // getter
            proto_net_tcp_socket& ps_socket(void);

            std::string ps_client_address(void);

        protected:

            virtual void ps_close_session(void);

        protected:

            proto_net_pipeline& ps_pipeline_;
            proto_net_tcp_socket socket_;
            bool session_read_error_;
            volatile bool read_complete_;
            size_t max_wait_msec_;
        };

    }

}

#endif
