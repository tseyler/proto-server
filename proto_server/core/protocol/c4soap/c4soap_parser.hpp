//
// Created by tseyler on 3/18/16.
//

#ifndef PROTO_SERVER_C4SOAP_PARSER_HPP_
#define PROTO_SERVER_C4SOAP_PARSER_HPP_

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace proto_net
{
    namespace protocol
    {
        namespace c4soap
        {
            class c4soap_parser
            {
            public:

                c4soap_parser(const std::string& c4soap_xml);
                virtual ~c4soap_parser();

            private:

                std::string c4soap_xml_;
                boost::property_tree::ptree pt_;
            };

        }
    }
}
#endif //PROTO_SERVER_C4SOAP_PARSER_HPP_
