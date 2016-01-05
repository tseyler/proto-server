
#include <boost/bind.hpp>
#include <core/server/proto_tcp_server.hpp>

using namespace boost::asio::ip;

namespace proto_net
{
    namespace server
    {

        proto_tcp_server::proto_tcp_server(proto_net_service& io_service, unsigned short port_num /* = 80*/)
                : proto_server(),
                  port_num_(port_num),
                  io_service_(io_service),
                  acceptor_(io_service, tcp::endpoint(tcp::v4(), port_num))
        {

        }

        proto_tcp_server::proto_tcp_server(proto_tcp_server& ps)
                : proto_server(),
                  port_num_(ps.ps_port()),
                  io_service_(ps.ps_service()),
                  acceptor_(ps.ps_service(), tcp::endpoint(tcp::v4(), ps.ps_port()))
        {

        }

        unsigned short
        proto_tcp_server::ps_port(void) const
        {
            return port_num_;
        }

        proto_net_service&
        proto_tcp_server::ps_service(void)
        {
            return io_service_;
        }

        void
        proto_tcp_server::ps_run(void)
        {
             io_service_.run();
        }

        void
        proto_tcp_server::ps_start_accept(proto_net_io& ps_io, size_t buffer_size)
        {

            proto_tcp_session* new_session = new proto_tcp_session(io_service_, ps_io, buffer_size);
            acceptor_.async_accept(new_session->ps_socket(),
                                   boost::bind(&proto_tcp_server::handle_accept, this, new_session, boost::asio::placeholders::error));
        }

        void
        proto_tcp_server::handle_accept(proto_tcp_session* session, const boost::system::error_code& error)
        {
            if (session)
            {
                proto_net_io& io = session->ps_io(); // get the session before it gets destroyed below
                size_t buffer_size = session->ps_buffer_size();
                if (!error)
                    session->start();
                else
                    delete session;

                ps_start_accept(io, buffer_size);
            }
            else {} // we will drop out because there is no session and no io
        }
    }



}
