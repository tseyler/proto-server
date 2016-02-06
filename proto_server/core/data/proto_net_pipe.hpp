//
// Created by tseyler on 1/26/16.
//

#ifndef PROTO_NET_PIPE_HPP_
#define PROTO_NET_PIPE_HPP_

#include <iostream>
#include <core/data/proto_net_data.hpp>

namespace proto_net
{
    namespace data
    {
        class proto_net_pipe
        {
        public:

            proto_net_pipe();
            proto_net_pipe(const proto_net_in_data& data_in);
            proto_net_pipe(const proto_net_pipe& pipe);
            virtual ~proto_net_pipe();

            virtual void clone(const proto_net_pipe& pipe);

            virtual proto_net_pipe& operator = (const proto_net_pipe& rhs);

            void ps_pipe_data_in(const proto_net_in_data &data_in);
            proto_net_in_data ps_pipe_data_in(void) const;

            virtual proto_net_out_data ps_pipe_data_out(void) const;

            friend std::ostream& operator << (std::ostream& out, const proto_net_pipe& pipe);
            friend std::istream& operator >> (std::istream& in, proto_net_pipe& pipe);

        protected:

            proto_net_in_out_data data_in_;

        };

        std::ostream& operator << (std::ostream& out, const proto_net_pipe& pipe);
        std::istream& operator >> (std::istream& in, proto_net_pipe& pipe);
    }
}

#endif //PROTO_NET_PIPE_HPP_
