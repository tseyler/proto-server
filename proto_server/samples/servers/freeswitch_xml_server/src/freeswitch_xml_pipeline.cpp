//
// Created by tseyler on 2/13/16.
//

#include <iostream>
#include <sstream>
#include "freeswitch_xml_pipeline.hpp"

using namespace proto_net::data;
using namespace proto_net::protocol;
using namespace proto_net::protocol::http;
using namespace proto_net::protocol::urlencode;

std::string xml_response =
 "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?><document type=\"freeswitch/xml\"><section name=\"result\"><result status=\"not found\" /></section></document>\r\n";

std::string http_response(const std::string& xml)
{
    std::string http_header_start = "HTTP/1.1 200 OK\r\nContent-Type: text/xml\r\nDate: Fri, 09 Mar 2016 17:41:44 GMT\r\nConnection: keep-alive\r\nContent-Length: ";

    std::stringstream ss;

    ss << http_header_start << xml.length() << "\r\n\r\n";
    ss << xml;

    return ss.str();
}

void
freeswitch_xml_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
{
    proto_net_string_data req_txt_data(req_data);
    //req_txt_data.data_type(data_text);

    std::cout << "Freeswitch XML Pipeline: Received = " << req_txt_data << std::endl;
    std::cout << std::endl;

    http_request_parser parser;
    http_request_message req_message;
    parser.protocol_parse(req_txt_data, req_message);

    std::string url_encoded = req_message.body().to_string();
    matches_t tokens;
    tokenize_urlencode_line(url_encoded, tokens);
    urlencode_key_values key_values;
    tokenize_urlencode_key_value(tokens, key_values);
    urlencode_key_values_iterator kvi = key_values.begin();
    while (kvi != key_values.end())
    {
        urlencode_key_value_pair kv_pair = *kvi++;
        std::cout << kv_pair.first << " = " << kv_pair.second << std::endl;
    }
    std::cout << std::endl;

    std::string response = http_response(xml_response);
    res_data = proto_net_out_data(response.c_str(), response.length());
    proto_net_out_data res_txt_data = res_data;
    res_txt_data.data_type(data_text);
    response = res_txt_data.to_string();
    std::cout << "Freeswitch XML Pipeline: Send = " << response;
}
