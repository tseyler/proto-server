
#include <boost/bind.hpp>
#include <core/server/proto_tcp_server.hpp>

using namespace boost::asio::ip;

namespace proto_net
{
    namespace server
    {

        proto_tcp_server::proto_tcp_server(unsigned short port_num /* = 80*/)
                : port_num_(port_num),
                  acceptor_(proto_net_service_ref(ps_service_), proto_net_tcp_endpoint(tcp::v4(), port_num))
        {

        }

        proto_tcp_server::proto_tcp_server(proto_tcp_server& ps)
                : port_num_(ps.ps_port()),
                  acceptor_(proto_net_service_ref(ps_service_), proto_net_tcp_endpoint(tcp::v4(), ps.ps_port()))
        {

        }

        unsigned short
        proto_tcp_server::ps_port(void) const
        {
            return port_num_;
        }

        void
        proto_tcp_server::ps_run(void)
        {
            ps_service_->run();
        }

        void
        proto_tcp_server::ps_start_accept(proto_net_io& ps_io, size_t buffer_size)
        {
            proto_tcp_session* new_session = new proto_tcp_session(ps_service_, ps_io, buffer_size);
            acceptor_.async_accept(new_session->ps_socket(),
                                   boost::bind(&proto_tcp_server::handle_accept, this, new_session,
                                               boost::asio::placeholders::error));
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
