//
// Created by tseyler on 1/26/16.
//

#include <sstream>
#include <core/data/proto_net_pipe.hpp>


namespace proto_net
{
    namespace data
    {
        proto_net_pipe::proto_net_pipe() : data_in_()
        {
        }

        proto_net_pipe::proto_net_pipe(const proto_net_in_data& data_in) : data_in_(data_in)
        {
        }

        proto_net_pipe::proto_net_pipe(const proto_net_pipe& pipe)
        {
            clone(pipe);
        }

        proto_net_pipe::~proto_net_pipe()
        {
        }

        void
        proto_net_pipe::clone(const proto_net_pipe& pipe)
        {
            data_in_ = pipe.ps_pipe_data_in();
        }

        proto_net_pipe&
        proto_net_pipe::operator = (const proto_net_pipe& rhs)
        {
            clone(rhs);

            return *this;
        }

        void
        proto_net_pipe::ps_pipe_data_in(const proto_net_in_data &data_in)
        {
            data_in_ = data_in;
        }

        proto_net_in_data
        proto_net_pipe::ps_pipe_data_in(void) const
        {
            return data_in_;
        }

        proto_net_out_data
        proto_net_pipe::ps_pipe_data_out(void) const
        {
            return data_in_;
        }

        std::ostream&
        operator << (std::ostream& out, const proto_net_pipe& pipe)
        {
            proto_net_out_data data_out = pipe.ps_pipe_data_out();
            out << data_out;

            return out;
        }

        std::istream&
        operator >> (std::istream& in, proto_net_pipe& pipe)
        {
            std::stringstream ss;
            char c;
            while (in)
            {
                in >> c;
                ss << c;
            }
            // assign the input to data
            proto_net_data data(ss.str());
            // use the assignment operator to update pipe
            pipe = proto_net_pipe(data);

            return in;
        }
    }
}

