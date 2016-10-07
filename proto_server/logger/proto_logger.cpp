//
// Created by tseyler on 10/7/16.
//

#include "proto_logger.hpp"


proto_logger_ptr
proto_logger::get_instance(void)
{
    static proto_logger_ptr blp;

    if (!blp)
        blp.reset(new proto_logger);

    return blp;
}

proto_logger::proto_logger()
{}

proto_logger::~proto_logger()
{}

void
proto_logger::log_debug(const std::string& log_str)
{
   // LOG4CPLUS_DEBUG(logger_, log_str);
}

void
proto_logger::log_debug(const std::stringstream& ss)
{
    log_debug(ss.str());
}

void
proto_logger::log_info(const std::string& log_str)
{
   // LOG4CPLUS_INFO(logger_, log_str);
}

void
proto_logger::log_info(const std::stringstream& ss)
{
    log_info(ss.str());
}

void
proto_logger::log_warn(const std::string& log_str)
{
   // LOG4CPLUS_WARN(logger_, log_str);
}

void
proto_logger::log_warn(const std::stringstream& ss)
{
    log_warn(ss.str());
}

void
proto_logger::log_error(const std::string& log_str)
{
   // LOG4CPLUS_ERROR(logger_, log_str);
}

void
proto_logger::log_error(const std::stringstream& ss)
{
    log_error(ss.str());
}

