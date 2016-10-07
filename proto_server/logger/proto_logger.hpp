//
// Created by tseyler on 10/7/16.
//

#ifndef PROTO_LOGGER_HPP_HPP_
#define PROTO_LOGGER_HPP_HPP_

#include <sstream>
#include <iostream>
#include <boost/shared_ptr.hpp>


define PROTO_LOG_DEBUG( msg )        proto_logger::get_instance()->log_debug( msg )
#define PROTO_LOG_INFO( msg )         proto_logger::get_instance()->log_info( msg )
#define PROTO_LOG_WARN( msg )         proto_logger::get_instance()->log_warn( msg )
#define PROTO_LOG_ERROR( msg )        proto_logger::get_instance()->log_error( msg )

class proto_logger;
typedef boost::shared_ptr<proto_logger> proto_logger_ptr;

class proto_logger
{
public:

    static proto_logger_ptr get_instance(void);

private:

    proto_logger();

public:

    virtual ~proto_logger();

    void log_debug(const std::string& log_str);
    void log_debug(const std::stringstream& ss);
    void log_info(const std::string& log_str);
    void log_info(const std::stringstream& ss);
    void log_warn(const std::string& log_str);
    void log_warn(const std::stringstream& ss);
    void log_error(const std::string& log_str);
    void log_error(const std::stringstream& ss);

};


#endif //PROTO_LOGGER_HPP_HPP_
