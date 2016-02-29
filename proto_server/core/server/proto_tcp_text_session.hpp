//
//  proto_tcp_text_session.hpp - base class for tcp text server sessions
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef PROTO_TCP_TEXT_SESSION_HPP_
#define PROTO_TCP_TEXT_SESSION_HPP_

#include <core/server/proto_tcp_session.hpp>

using namespace boost::asio::ip;
using namespace proto_net::data;

namespace proto_net
{
    namespace server
    {
        class proto_tcp_text_session : public proto_tcp_session
        {
        public:

            proto_tcp_text_session(proto_net_service_ptr ps_service, proto_net_pipeline& ps_pipeline,
                             size_t buffer_size = 4096);
            virtual ~proto_tcp_text_session();

            virtual void ps_start(void);
            virtual void ps_async_read(void);
            virtual void ps_async_write(proto_net_out_data& data_out);

            virtual void ps_handle_read(const boost::system::error_code &error, size_t bytes_transferred);
            virtual void ps_handle_write(const boost::system::error_code &error);

        protected:

            boost::asio::streambuf stream_buffer_;
        };
    }

}

#endif
