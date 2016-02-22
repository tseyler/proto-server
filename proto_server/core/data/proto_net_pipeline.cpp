//
// Created by tseyler on 2/5/16.
//

#include <core/data/proto_net_pipeline.hpp>

namespace proto_net
{
    namespace data
    {
        proto_net_pipeline::proto_net_pipeline() : io_(NULL), /*mutex_locked_(false),*/ ps_(NULL)
        {}
        proto_net_pipeline::~proto_net_pipeline()
        {
            //if (mutex_locked_)
                //ps_pipeline_unlock();
        }

        proto_service*
        proto_net_pipeline::ps_proto_service(void ) const
        {
            return ps_;
        }

        proto_async_io*
        proto_net_pipeline::ps_proto_io(void) const
        {
            return io_;
        }

        void
        proto_net_pipeline::ps_proto_service(proto_service* ps)
        {
            ps_ = ps;
        }

        void
        proto_net_pipeline::ps_proto_io(proto_async_io* io)
        {
            io_ = io;
        }

//        void
//        proto_net_pipeline::ps_pipeline_lock(void)
//        {
//            mutex_.lock();
//            mutex_locked_ = true;
//        }

//        void
//        proto_net_pipeline::ps_pipeline_unlock(void)
//        {
//            mutex_.unlock();
//            mutex_locked_ = false;
//        }

//        bool
//        proto_net_pipeline::ps_pipeline_try_lock(void)
//        {
//            return mutex_locked_ = mutex_.try_lock();
//        }
//
//        bool
//        proto_net_pipeline::ps_pipeline_is_locked(void)
//        {
//            return mutex_locked_;
//        }

        proto_net_empty_pipeline empty_pipeline_inst {};

    }
}

