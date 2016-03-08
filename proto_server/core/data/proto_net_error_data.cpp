
#include <boost/assign/list_inserter.hpp>
#include <core/data/proto_net_error_data.hpp>

namespace proto_net
{
    namespace data
    {
        proto_net_error_code_map proto_net_error_data::error_code_map_;

        void
        proto_net_error_data::create_error_code_map(void)
        {
            if (!error_code_map_.size())
            {
                boost::assign::insert(error_code_map_)
                        (ec_success, "success")
                        (ec_general_error, "unspecified general error")
                        (ec_data_size_error, "data size error where the data is not available")
                        (ec_connect_error, "TCP connection error")
                        (ec_read_error, "error occurred while doing a read")
                        (ec_write_timeout_error, "write timeout error (no response)");
            }
        }

        proto_net_error_data::proto_net_error_data(proto_net_data_error_code ec /*= ec_success*/) :
                proto_net_data(data_error), ec_(ec), error_message_("Success")
        {
            proto_net::data::proto_net_error_data::create_error_code_map();
            error_message_ = error_code_map_[ec_];
        }

        proto_net_error_data::proto_net_error_data(const std::string& ec_message,
                                                   proto_net_data_error_code ec /*= ec_success*/) :
                proto_net_data(data_error), ec_(ec), error_message_(ec_message)
        {
            proto_net::data::proto_net_error_data::create_error_code_map();
        }

        proto_net_error_data::~proto_net_error_data()
        {}
    }
}