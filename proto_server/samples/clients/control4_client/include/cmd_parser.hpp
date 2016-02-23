

#ifndef CMD_PARSER_HPP__
#define CMD_PARSER_HPP__

#include <iostream>
#include <string.h>
#include <map>
#include <boost/algorithm/string.hpp>

#include "director.hpp"

#define SAFE_INDEX( idx, cnt )	(idx < cnt)

#define IS_EXIT( cmd ) (boost::iequals(cmd, "quit") || boost::iequals(cmd, "exit"))

class cmd_parser
{
public:

	cmd_parser(char** args, int cnt);
	cmd_parser(const std::string& raw_string);


	std::string host(void) { return host_; }
	std::string cmd(void) { return cmd_; }
	bool parsed(void) {return parsed_; }

	std::string to_authenticate(int& seq);
	std::string to_c4soap(int& seq);

	bool parse(const std::string& raw_string);

private:

	void initialize_command_map(void);

	// setters
	void set_command(std::string& cmd, director::params_array& params_);

private:

	std::string host_;
	std::string cmd_;
	bool parsed_;

	director::params_array params_;

	std::map<std::string, director::director_c4soap_function> director_command_map;
};

#endif