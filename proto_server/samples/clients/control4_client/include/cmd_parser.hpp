

#ifndef CMD_PARSER_HPP_
#define CMD_PARSER_HPP_

#include <iostream>
#include <string.h>
#include <map>
#include <boost/algorithm/string.hpp>

#include <core/protocol/c4soap/c4soap_director.hpp>

#define SAFE_INDEX( idx, cnt )	(idx < cnt)

#define IS_EXIT( cmd ) (boost::iequals(cmd, "quit") || boost::iequals(cmd, "exit"))

using namespace proto_net::protocol;

class cmd_parser
{
public:

	cmd_parser(char** args, int cnt);
	cmd_parser(const std::string& raw_string);


	std::string host(void) { return host_; }
	std::string cmd(void) { return cmd_; }
	bool parsed(void) {return parsed_; }

	std::string to_authenticate(unsigned long& seq);
	std::string to_c4soap(unsigned long& seq);

	bool parse(const std::string& raw_string);

private:

	void initialize_command_map(void);

	// setters
	void set_command(std::string& cmd, c4soap::params_array& params_);

private:

	std::string host_;
	std::string cmd_;
	bool parsed_;

	c4soap::params_array params_;

	std::map<std::string, c4soap::director_c4soap_function> director_command_map;
};

#endif