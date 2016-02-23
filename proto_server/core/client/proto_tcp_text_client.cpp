//
// Created by tseyler on 1/13/16.
//
#include <ostream>
#include <istream>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <core/client/proto_tcp_text_client.hpp>


namespace proto_net
{
    namespace client
    {
        proto_tcp_text_client::proto_tcp_text_client(const std::string& address,
                                           unsigned short port_num /* = 80*/,
                                           proto_net_pipeline& ps_pipeline/* = empty_pipeline_inst*/,
                                           size_t buffer_size /*= 4096*/)
                : proto_tcp_client(address, port_num, ps_pipeline, buffer_size)
        {}

        proto_tcp_text_client::~proto_tcp_text_client()
        {}

        proto_tcp_text_client::proto_tcp_text_client(proto_net_service_ptr ps_service, const std::string& address,
                                                     unsigned short port_num /* = 80*/,
                                                     proto_net_pipeline& ps_pipeline/* = empty_pipeline_inst*/,
                                                     size_t buffer_size /*= 4096*/)
                : proto_tcp_client(ps_service, address, port_num, ps_pipeline, buffer_size)
        {}

        void
        proto_tcp_text_client::ps_async_read(void)
        {
            boost::asio::async_read_until(socket_, read_stream_buffer_, '\0',
                                          boost::bind(&proto_tcp_text_client::ps_handle_read, this,
                                                      boost::asio::placeholders::error,
                                                      boost::asio::placeholders::bytes_transferred));
        }

        void
        proto_tcp_text_client::ps_async_write(proto_net_in_data& data_in)
        {

            if (data_in.data() && data_in.data_size() && data_in.data_type() == data_text) //guard against empty data getting put into the pipe in
            {
                ps_write_spin_lock(); // wait for previous write to complete

                ps_pipeline_.ps_pipe_in(data_in); // just prior to the write, execute the pipe_in

                char *data = data_in.data();
                size_t data_size = data_in.data_size();
                if (data && data_size)
                {
                    boost::asio::async_write(socket_, boost::asio::buffer(data, data_size),
                                             boost::bind(&proto_tcp_text_client::ps_handle_write, this,
                                                             boost::asio::placeholders::error,
                                                             boost::asio::placeholders::bytes_transferred));
                    write_complete_ = false;
                }
                else
                    ps_async_read(); // just go back to reading
            }
            else
                ps_async_read(); // just go back to reading
        }

        void
        proto_tcp_text_client::ps_handle_read(const boost::system::error_code& error, size_t bytes_transferred)
        {
            if (!error)
            {
                std::istream is(&read_stream_buffer_);
                is.get(buffer_, buffer_size_, '\0');

                // handle a ps_read here
                std::string response(buffer_);
                proto_net_data res_data(response);
                std::string request;
                proto_net_data req_data(request);
                if (res_data.data_size())
                {
                    ps_pipeline_.ps_pipeline(res_data, req_data); // response and request are reversed here
                    ps_pipeline_.ps_pipe_out(res_data); // post read, execute the pipe_out for the client
                }
                read_stream_buffer_.consume(read_stream_buffer_.size());
                read_stream_buffer_.prepare(buffer_size_);
                write_complete_ = true;

                ps_async_read(); // done go back to reading
            }
            else
                delete this; // for now
        }

        void
        proto_tcp_text_client::ps_handle_write(const boost::system::error_code &error, size_t bytes_transferred)
        {
            if (!error)
            {
                // handle a post write here
                ps_async_read(); // just go back to reading
            }
            else
                delete this;
        }

    }
}