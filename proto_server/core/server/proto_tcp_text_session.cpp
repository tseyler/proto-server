//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <boost/bind.hpp>
#include <core/server/proto_tcp_text_session.hpp>

using namespace boost::asio::ip;

namespace proto_net
{
    namespace server
    {
        proto_tcp_text_session::proto_tcp_text_session(proto_net_service_ptr ps_service, proto_net_pipeline& ps_pipeline,
                                             size_t buffer_size /*= 4096*/)
                : proto_tcp_session(ps_service, ps_pipeline, buffer_size)
        { }

        proto_tcp_text_session::~ proto_tcp_text_session()
        {

        }

        void
        proto_tcp_text_session::ps_start(void)
        {
            ps_async_read();
        }

        void
        proto_tcp_text_session::ps_async_read(void)
        {
            stream_buffer_.prepare(buffer_size_);
            boost::asio::async_read_until(socket_, stream_buffer_, '\0',
                                          boost::bind(&proto_tcp_text_session::ps_handle_read, this,
                                                      boost::asio::placeholders::error,
                                                      boost::asio::placeholders::bytes_transferred));
        }


        void
        proto_tcp_text_session::ps_async_write(proto_net_out_data& data_out)
        {
            if (data_out.data() && data_out.data_size() && data_out.data_type() == data_text) //guard against empty data getting put into the pipe in
            {
                // add pre-write pipe out call for the pipeline
                ps_pipeline_.ps_pipe_out(data_out); // (server) any changes to the out data just prior to being sent
                char *data = data_out.data();
                size_t data_size = data_out.data_size();
                if (data && data_size)
                {
                    //data_size++; // increase by 1
                    boost::asio::async_write(socket_, boost::asio::buffer(data, data_size),
                                             boost::bind(&proto_tcp_session::ps_handle_write, this,
                                                         boost::asio::placeholders::error));
                }
                else
                    ps_async_read(); // just go back to reading
            }
            else
                ps_async_read(); // just go back to reading
        }

        void
        proto_tcp_text_session::ps_handle_read(const boost::system::error_code &error, size_t bytes_transferred)
        {
            if (session_read_error_)
                return;

            if (!error)
            {
                std::istream is(&stream_buffer_);
                is.get(buffer_, buffer_size_, '\0');

                // handle a ps_read here
                std::string request(buffer_);
                proto_net_data req_data(request);
                std::string response;
                proto_net_data res_data(response);
                if (req_data.data_size())
                {
                    ps_pipeline_.ps_pipe_in(req_data); // just prior to the pipeline execute the pipe in
                    ps_pipeline_.ps_pipeline(req_data, res_data); // all of the magic takes place inside the ps_pipeline
                }
                stream_buffer_.consume(bytes_transferred);
                ps_async_write(res_data); // set response data ptr or size to zero for a non-write
            }
            else
            {
                ps_close_session();
                session_read_error_ = true;
            }
        }

        void
        proto_tcp_text_session::ps_handle_write(const boost::system::error_code& error)
        {
            if (!error)
            {
                // handle a post write here
                ps_async_read(); // just go back to reading
            }
        }
    }

}