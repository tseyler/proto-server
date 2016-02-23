//
// Created by tseyler on 1/13/16.
//

#ifndef PROTO_TCP_CLIENT_HPP_
#define PROTO_TCP_CLIENT_HPP_

#include <core/proto_async_io.hpp>
#include <core/client/proto_client.hpp>

namespace proto_net
{
    namespace client
    {
        class proto_tcp_client : public proto_async_io, public proto_client
        {
        public:

            proto_tcp_client(const std::string& address, unsigned short port_num = 80,
                             proto_net_pipeline& ps_pipeline = empty_pipeline_inst,
                             size_t buffer_size = 4096);
            proto_tcp_client(proto_net_service_ptr ps_service, const std::string& address,
                             unsigned short port_num = 80,
                             proto_net_pipeline& ps_pipeline = empty_pipeline_inst,
                             size_t buffer_size = 4096);
            virtual ~proto_tcp_client();

            // pure virtuals - ps_async_io
            virtual void ps_async_read(void);
            virtual void ps_async_write(proto_net_in_data& data_in);
            virtual proto_net_pipeline& ps_pipeline(void);

            virtual void ps_async_connect(const proto_net_in_data& write__data);
            virtual void ps_handle_resolve(const boost::system::error_code &error,
                                           boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
            virtual void ps_handle_connect(const boost::system::error_code &error,
                                           boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
            virtual void ps_handle_read(const boost::system::error_code &error, size_t bytes_transferred);
            virtual void ps_handle_write(const boost::system::error_code &error, size_t bytes_transferred);

            // getter
            proto_net_tcp_socket& ps_socket(void);

        protected:

            virtual bool ps_write_spin_lock(void);

        protected:

            std::string address_;
            unsigned short port_num_;
            proto_net_tcp_socket socket_;
            proto_net_tcp_resolver resolver_;
            proto_net_pipeline& ps_pipeline_;
            size_t buffer_size_;
            char* buffer_;
            proto_net_in_data write_data_;
            volatile bool write_complete_;
        };

        // specialization of a pipeline used by servers for a downstream client
        class proto_tcp_downstream_pipeline : public proto_net_pipeline
        {
        public:

            virtual void ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data);
            virtual void ps_pipe_in(proto_net_in_data& in_data);
            virtual void ps_pipe_out(proto_net_out_data& out_data);
        };
    }
}


#endif //PROTO_TCP_CLIENT_HPP_
