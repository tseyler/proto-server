//
// Created by tseyler on 2/3/16.
//

#include "sipclient_logger.hpp"

namespace sipclient
{
    sipclient_logger::sipclient_logger(std::ostream& os) : os_(os.rdbuf())
    {

    }

    void
    sipclient_logger::sipclient_log(const std::string& class_name, const std::string& function_name,
                       int line, const std::string& log_msg)
    {
        std::stringstream ss;
        ss << class_name << "::" << function_name << ":" << line << ": " << log_msg << std::endl;
        os_ << ss.str();
    }

    void
     sipclient_logger::sipclient_log(const std::string& class_name, const std::string& function_name,
                       int line, const std::stringstream& ss)
    {
        sipclient_log(class_name, function_name, line, ss.str());
    }

}

