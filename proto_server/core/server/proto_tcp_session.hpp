//
// Created by Terry Seyler on 8/30/15.
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
            virtual void ps_async_write(proto_net_out_data& data_out);
            virtual proto_net_pipeline& ps_pipeline(void);

            virtual void ps_handle_read(const boost::system::error_code &error, size_t bytes_transferred);
            virtual void ps_handle_write(const boost::system::error_code &error);


            // getter
            proto_net_tcp_socket& ps_socket(void);

        protected:

            proto_net_pipeline& ps_pipeline_;
            proto_net_tcp_socket socket_;
        };


        // specialization of a pipeline used by clients for an upstream session
        class proto_tcp_upstream_pipeline : public proto_net_pipeline
        {
        public:

            virtual void ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data);
            virtual void ps_pipe_in(proto_net_in_data& in_data);
            virtual void ps_pipe_out(proto_net_out_data& out_data);
        };
    }

}

#endif
