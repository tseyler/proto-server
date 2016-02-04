//
// Created by tseyler on 2/3/16.
//

#ifndef SIPCLIENT_LOGGER_HPP_
#define SIPCLIENT_LOGGER_HPP_

#include <memory>
#include <sstream>
#include <iostream>


namespace sipclient
{

    class sipclient_logger;
    typedef std::shared_ptr<sipclient_logger> sipclient_logger_ptr;

    class sipclient_logger
    {
    public:

        sipclient_logger(std::ostream& os);

        void sipclient_log(const std::string& class_name, const std::string& function_name,
                           int line, const std::string& log_msg);
        void sipclient_log(const std::string& class_name, const std::string& function_name,
                           int line, const std::stringstream& ss);

    protected:

        std::ostream os_;
    };

}

#endif //SIPCLIENT_LOGGER_HPP_
