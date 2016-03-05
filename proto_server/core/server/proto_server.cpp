//
// Created by tseyler on 1/6/16.
//

#include <core/server/proto_server.hpp>

namespace proto_net
{
    namespace server
    {
        proto_server::proto_server() : ps_service_(new proto_net_service)
        {
            proto_net::data::proto_net_error_data::create_error_code_map();
        }

        proto_server::proto_server(proto_net_service_ptr ps_service) : ps_service_(ps_service)
        {
            proto_net::data::proto_net_error_data::create_error_code_map();
        }

        proto_server::~proto_server()
        {
        }

        void
        proto_server::ps_run(void)
        {
            ps_service_->run();
        }

        void proto_server::ps_start(void)
        {
            if (!ps_thread_)
            {
                ps_thread_.reset(new boost::thread(boost::bind(&boost::asio::io_service::run, ps_service_.get())));
            }
        }

        void
        proto_server::ps_stop(void)
        {
            ps_service_->stop();

            if (ps_thread_)
            {
                ps_thread_->join();
                ps_thread_.reset();
            }

            ps_service_->reset();
        }
    }
}