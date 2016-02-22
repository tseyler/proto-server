//
// Created by Terry Seyler on 10/25/15.
//

#ifndef PROTO_NET_PIPELINE_HPP_
#define PROTO_NET_PIPELINE_HPP_

#include <core/proto_async_io.hpp>
#include <core/proto_service.hpp>
#include <core/data/proto_net_data.hpp>
#include <core/proto_net_types.hpp>


namespace proto_net
{
    namespace data
    {
        class proto_net_pipeline
        {
        public:

            proto_net_pipeline();
            virtual ~proto_net_pipeline();

            virtual void ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data) = 0;  // the response data
            virtual void ps_pipe_in(proto_net_in_data& in_data) = 0;
            virtual void ps_pipe_out(proto_net_out_data& out_data) = 0;

            // getters
            proto_service*  ps_proto_service(void ) const;
            proto_async_io* ps_proto_io(void) const;
            //setter
            void ps_proto_service(proto_service* ps);
            void ps_proto_io(proto_async_io* io);
           // void ps_pipeline_lock(void);
          //  void ps_pipeline_unlock(void);
           // bool ps_pipeline_try_lock(void);
         //   bool ps_pipeline_is_locked(void);

        protected:

            proto_async_io* io_;
            //bool mutex_locked_;
            proto_net_mutex mutex_;

        private:

            proto_service* ps_;
        };

        // specialization with empty implementation
        class proto_net_empty_pipeline : public proto_net_pipeline
        {
        public:

            void ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data) {} // empty
            void  ps_pipe_in(proto_net_in_data& in_data) {}
            void ps_pipe_out(proto_net_out_data& out_data) {}
        };

        extern proto_net_empty_pipeline empty_pipeline_inst;


    }
}
#endif //PROTO_NET_PIPELINE_HPP_
