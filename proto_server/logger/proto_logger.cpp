//
// Created by tseyler on 10/7/16.
//

#include <ctime>
#include "proto_logger.hpp"



void
proto_logger_time(std::stringstream& ss_out)
{
    std::time_t t = std::time(NULL);
    char time_str[128];
    std::strftime(time_str, sizeof(time_str), "%a, %d %b %Y %T: ",std::localtime(&t));
    ss_out << time_str;
}


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
    std::stringstream ss_out;
    proto_logger_time(ss_out);

    std::cout << ss_out << "DEBUG:: " << log_str << std::endl;
}

void
proto_logger::log_debug(const std::stringstream& ss)
{
    std::stringstream ss_out;
    proto_logger_time(ss_out);

    std::cout << ss_out << "DEBUG:: " << ss << std::endl;
}

void
proto_logger::log_info(const std::string& log_str)
{
    std::stringstream ss_out;
    proto_logger_time(ss_out);

    std::cout << ss_out << "INFO:: " << log_str << std::endl;
}

void
proto_logger::log_info(const std::stringstream& ss)
{
    std::stringstream ss_out;
    proto_logger_time(ss_out);

    std::cout << ss_out << "INFO:: " << ss << std::endl;
}

void
proto_logger::log_warn(const std::string& log_str)
{
    std::stringstream ss_out;
    proto_logger_time(ss_out);

    std::cout << ss_out << "WARN:: " << log_str << std::endl;
}

void
proto_logger::log_warn(const std::stringstream& ss)
{
    std::stringstream ss_out;
    proto_logger_time(ss_out);

    std::cout << ss_out << "WARN:: " << ss << std::endl;
}

void
proto_logger::log_error(const std::string& log_str)
{
    std::stringstream ss_out;
    proto_logger_time(ss_out);

    std::cout << ss_out << "ERROR:: " << log_str << std::endl;
}

void
proto_logger::log_error(const std::stringstream& ss)
{
    std::stringstream ss_out;
    proto_logger_time(ss_out);

    std::cout << ss_out << "ERROR:: " << ss << std::endl;
}

