//
//  Copyright (c) 2015 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <sstream>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <core/protocol/net_parse_routines.hpp>
#include <core/protocol/http/http_constants.hpp>
#include <core/protocol/http/http_parse_routines.hpp>

namespace proto_net
{
	namespace protocol
	{
		namespace http
		{
			const std::string method_pat = "OPTIONS|GET|HEAD|POST|PUT|DELETE|TRACE|CONNECT";
			const std::string http_ver_pat = "HTTP/(1\\.0|1\\.1)";
			const std::string abs_uri_pat = "^(ftp|http|https):\\/\\/(\\w+\\.)*(\\w*)\\/([\\w\\d]+\\/{0,1})+";
			//    const std::string rel_uri_pat = "^\\/(\\w+\\.)*(\\w*)\\/([\\w\\d]+\\/{0,1})+";
			const std::string rel_uri_pat = "^\\/(\\w+\\.)*";
			const std::string server_pat = "^\\*$";
			const std::string server_method_pat = "OPTIONS";
			const std::string status_code_pat = "^[1-5]{1}\\d{2}$";
			const std::string request_header_field_pat =
					"Accept|Accept-Charset|Accept-Encoding|"
							"Accept-Language|Authorization|Expect|"
							"From|Host|If-Match|If-Modified-Since|"
							"If-None-Match|If-Range|If-Unmodified-Since|"
							"Max-Forwards|Proxy-Authorization|Range|Referer|TE|User-Agent";
			const std::string general_header_field_pat =
					"Cache-Control|Connection|Date|Pragma|Trailer|"
							"Transfer-Encoding|Upgrade|Via|Warning";
			const std::string entity_header_field_pat =
					"Allow|"
							"Content-Encoding|"
							"Content-Language|"
							"Content-Length|"
							"Content-Location|"
							"Content-MD5|"
							"Content-Range|"
							"Content-Type|"
							"Expires|"
							"Last-Modified";
			const std::string response_header_field_pat =
					"Accept-Ranges|"
							"Age|"
							"ETag|"
							"Location|"
							"Proxy-Authenticate|"
							"Retry-After|"
							"Server|"
							"Vary|"
							"WWW-Authenticate";

			std::string header_field_all_pat(void)
			{
				std::stringstream ss;
				ss << request_header_field_pat;
				ss << "|" << general_header_field_pat;
				ss << "|" << entity_header_field_pat;
				ss << "|" << response_header_field_pat;

				return ss.str();
			}

			// return a pattern by its name
			std::string get_pattern(const std::string &pattern_name)
			{
				std::string pat;

				if (boost::equals(pattern_name, http_headers::general_category))
					pat = general_header_field_pat;
				if (boost::equals(pattern_name, http_headers::request_category))
					pat = request_header_field_pat;
				if (boost::equals(pattern_name, http_headers::entity_category))
					pat = entity_header_field_pat;
				if (boost::equals(pattern_name, http_headers::response_category))
					pat = response_header_field_pat;

				return pat;
			}


			size_t
			find_crlf(const std::string &str, size_t pos)
			{
				return str.find(http::crlf, pos);
			}

			size_t
			find_line(const std::string &str, std::string &line, size_t pos)
			{
				size_t end_pos = find_crlf(str, pos);
				if (end_pos != std::string::npos)
				{
					line = trim(str.substr(pos, end_pos - pos));
					end_pos += 2;
				}

				return end_pos;
			}

			size_t
			get_lines(const std::string &http, http::lines_t &lines)
			{
				size_t pos(0);
				size_t count(0);

				while (pos != std::string::npos)
				{
					std::string line;
					pos = find_line(http, line, pos);
					if (pos != std::string::npos)
					{
						lines.push_back(line);
						count++;
					}
				}

				return count;
			}

			size_t
			get_header_field_lines(const lines_t &http_lines, lines_t &header_field_lines)
			{
				size_t count(0);

				lines_t_const_iterator it = http_lines.begin();
				while (it != http_lines.end())
				{
					std::string line = *it++;
					if (search_pattern(line, header_field_all_pat()))
					{
						count++;
						header_field_lines.push_back(line);
					}
				}

				return count;
			}

			size_t
			message_body_position(const proto_net_string_data &data)
			{
				size_t pos(0);
				size_t cr_found(0);
				size_t lf_found(0);
				size_t line_found(0);
				char *byte_data = data.data();

				for (size_t p = 0;
					 p <= data.data_size();
					 p++)
				{
					if (p == (lf_found + 1))
					{
						if (cr_found == (lf_found - 1)) // we just found a line
						{
							if (p == (line_found + 2)) // two crlf's
							{
								pos = p;
								break;
							}
							line_found = p;
						}
					}
					if (byte_data[p] == lf)
					{
						lf_found = p;
						continue;
					}
					if (byte_data[p] == cr)
						cr_found = p;
				}

				return pos;
			}

			size_t
			tokenize_http_line(const std::string line, matches_t &tokens)
			{
				std::string sep(" \t");
				split(line, sep, tokens);

				return tokens.size();
			}

			size_t
			tokenize_header_field(const std::string line, matches_t &tokens)
			{
				std::string sep(":");
				split(line, sep, tokens);
				if (tokens.size() == 2)
				{
					tokens[0] = trim(tokens[0]);
					tokens[1] = trim(tokens[1]);
				}

				return tokens.size();
			}

			http_parse_result
			validate_request_method(const std::string method)
			{
				return search_pattern(method, method_pat) ? http_parse_success : http_request_method_error;
			}

			http_parse_result
			validate_request_uri(const std::string &uri, const std::string &method)
			{
				bool res(false);

				if (search_pattern(method, server_method_pat))
				{
					res = search_pattern(uri, server_pat); // check for asterisk
				}
				else
				{
					res = search_pattern(uri, abs_uri_pat); // check for an absolute URI
					if (!res)// check for a relative uri
					{
						res = search_pattern(uri, rel_uri_pat);
					}
				}

				return res ? http_parse_success : http_uri_error;
			}

			http_parse_result
			validate_http_version(const std::string &http_version)
			{
				return search_pattern(http_version, http_ver_pat) ? http_parse_success : http_version_error;
			}

			http_parse_result
			validate_request_line(matches_t &tokens)
			{
				http_parse_result res(http_parse_success);

				if (tokens.size() == 3) // method, request_uri, http_version
				{
					res = validate_request_method(tokens[0]);
					if (HTTP_PARSE_SUCCEEDED(res))
					{
						res = validate_request_uri(tokens[1], tokens[0]);
						if (HTTP_PARSE_SUCCEEDED(res))
							res = validate_http_version(tokens[2]);
					}
				}
				else
					res = http::http_format_error;

				return res;
			}

			http_parse_result
			validate_header_field(matches_t &tokens, const std::string &field_name_pat)
			{
				http_parse_result res(http_parse_success);

				if (tokens.size() == 2)
					res = search_pattern(tokens[0], field_name_pat) ? http_parse_success : http_header_field_error;
				else
					res = http_format_error;

				return res;
			}

			http_parse_result
			validate_header_fields(const lines_t &lines, const std::string &category, http_header_fields &http_fields)
			{
				http_parse_result res(http_parse_success);
				std::string pat = get_pattern(category);
				if (pat.length() > 0)
				{
					lines_t_const_iterator it = lines.begin();
					while (it != lines.end())
					{
						std::string line = *it++;
						matches_t tokens;
						if (tokenize_header_field(line, tokens))
						{
							http::http_parse_result line_res = validate_header_field(tokens, pat);
							if (HTTP_PARSE_SUCCEEDED(line_res))
								// set in http_fields
								http_fields.set_header_field(tokens[0], tokens[1]);
						}
						else
							res = http_format_error;
					}
				}
				else
					res = http_parse_internal_error;

				return res;
			}

			http::http_parse_result
			validate_http_headers(const http::lines_t &lines, http::http_headers &headers)
			{
				http::http_parse_result res(http::http_parse_success);
				http::http_headers_map &hdr_map = headers.get_headers_map();
				for (http::http_headers_map_iterator it = hdr_map.begin();
					 it != hdr_map.end();
					 it++)
				{
					std::string category = (*it).first;
					http::http_header_fields &fields = (*it).second;
					res = validate_header_fields(lines, category, fields);
					if (!HTTP_PARSE_SUCCEEDED(res))
						break;
				}

				return res;
			}

			http_parse_result
			validate_status_code(const std::string &status_code)
			{
				return search_pattern(status_code, http::status_code_pat) ? http_parse_success : http_status_code_error;
			}

			http_parse_result
			validate_status_line(matches_t &tokens)
			{
				http_parse_result res(http_parse_success);

				if (tokens.size() == 3) // http_version, status_code, reason_phrase
				{
					res = validate_http_version(tokens[0]);
					if (HTTP_PARSE_SUCCEEDED(res))
					{
						res = validate_status_code(tokens[1]);
					}
				}
				else
					res = http_format_error;

				return res;
			}
		}
	}
}
