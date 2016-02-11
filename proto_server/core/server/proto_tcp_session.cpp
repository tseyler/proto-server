
#include <boost/bind.hpp>
#include <core/server/proto_tcp_session.hpp>

using namespace boost::asio::ip;

namespace proto_net
{
    namespace server
    {
        proto_tcp_session::proto_tcp_session(proto_net_service_ptr ps_service, proto_net_pipeline& ps_pipeline,
                                             size_t buffer_size /*= 4096*/) :
                proto_session(ps_pipeline, buffer_size),
                socket_(proto_net_service_ref(ps_service))
        {

        }

        proto_tcp_session::~proto_tcp_session()
        {

        }

        void
        proto_tcp_session::ps_start(void)
        {
            ps_async_read();
        }

        void
        proto_tcp_session::ps_async_read(void)
        {

            socket_.async_read_some(boost::asio::buffer(buffer_, buffer_size_),
                                    boost::bind(&proto_tcp_session::ps_handle_read, this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));

            /*
            boost::asio::streambuf b;
            boost::asio::async_read_until(socket_, b, '\0',
                                          boost::bind(&client::handle_read_status_line, this,
                                                      boost::asio::placeholders::error));

            char buf[buffer_size_];
            memset(buf, 0, buffer_size_);
            boost::asio::streambuf b;
            if (boost::asio::read_until(socket_, b, '\0'))
            {
                std::istream is(&b);
                is.get(buf, buffer_size_, '\0');
            }
            */
        }


        void
       // proto_tcp_session::ps_async_write(const char *data, size_t data_size)
        proto_tcp_session::ps_async_write(proto_net_out_data& data_out)
        {
            // add pre-write pipe out call for the pipeline
            ps_pipeline_.ps_pipe_out(data_out); // (server) any changes to the out data just prior to being sent
            char* data = data_out.data();
            size_t data_size = data_out.data_size();
            //proto_net_data_type dt = data_out.data_type();
            //if (dt == data_text)
             //   data_size++;    // add a null character for null terminated strings
            if (data && data_size)
            {
                boost::asio::async_write(socket_, boost::asio::buffer(data, data_size),
                                         boost::bind(&proto_tcp_session::ps_handle_write, this,
                                                     boost::asio::placeholders::error));
            }
            else
                ps_async_read(); // just go back to reading
        }

        void
        proto_tcp_session::ps_handle_read(const boost::system::error_code &error, size_t bytes_transferred)
        {
            if (!error)
            {
              // handle a ps_read here
                proto_net_data req_data(buffer_, bytes_transferred);
                proto_net_data res_data;
                ps_pipeline_.ps_pipe_in(req_data); // just prior to the pipeline execute the pipe in
                ps_pipeline_.ps_pipeline(req_data, res_data); // all of the magic takes place inside the ps_io_ object
                ps_async_write(res_data); // set response data ptr or size to zero for a non-write
            }
            else
                delete this; // for now
        }

        void
        proto_tcp_session::ps_handle_write(const boost::system::error_code &error)
        {
            if (!error)
            {
                // handle a post write here
                ps_async_read(); // just go back to reading
            }
            else
                delete this;
        }

        proto_net_tcp_socket&
        proto_tcp_session::ps_socket(void)
        {
            return socket_;
        }
    }

}