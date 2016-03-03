

#include <core/data/proto_net_error_data.hpp>


namespace proto_net
{
    namespace data
    {
        proto_net_error_data::proto_net_error_data(proto_net_data_error_code ec /*= ec_success*/) :
                proto_net_data(data_error), ec_(ec), error_message_("Success")
        {}

        proto_net_error_data::proto_net_error_data(const std::string& ec_message,
                                                   proto_net_data_error_code ec /*= ec_success*/) :
                proto_net_data(data_error), ec_(ec), error_message_(ec_message)
        {}

        proto_net_error_data::~proto_net_error_data()
        {}
    }
}