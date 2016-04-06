//
//  http_constants.hpp - constants for HTTP routines
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef HTTP_CONSTANTS_HPP_
#define HTTP_CONSTANTS_HPP_

#include <string>
namespace proto_net
{
    namespace protocol
    {
        namespace http
        {
            const std::string sp = " ";
            const std::string crlf = "\r\n";
            const std::string colon = ":";
            const char cr = '\r';
            const char lf = '\n';
        }
    }
}

#endif
