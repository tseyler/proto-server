//
// Created by tseyler on 1/6/16.
//

#include <core/client/proto_client.hpp>

namespace proto_net
{
    namespace client
    {
        proto_client::proto_client() : ps_service_(new proto_net_service)
        {}

        proto_client::proto_client(proto_net_service_ptr ps_service) : ps_service_(ps_service)
        {}

        proto_client::~proto_client()
        {}

        void
        proto_client::ps_run(void)
        {
            ps_service_->run();
        }

        void proto_client::ps_start(void)
        {
            if (!ps_thread_)
            {
                ps_thread_.reset(new boost::thread(boost::bind(&boost::asio::io_service::run, ps_service_.get())));
            }
            boost::this_thread::sleep(boost::posix_time::milliseconds(100));
        }

        void
        proto_client::ps_stop(void)
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