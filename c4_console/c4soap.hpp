
#ifndef C4SOAP_HPP__
#define C4SOAP_HPP__

#include <string.h>
#include <sstream>

namespace c4soap
{
	// this is how you begin a c4soap message
	void begin_c4soap_message(std::stringstream& ss, 
								const std::string& cmd, 
								int& seq, 
								bool async = false);

	// this is how you end a c4soap message
	void end_c4soap_message(std::stringstream& ss);

	// returns a param where the value is a string:
	// <param name="foo" type="string">bar</param>
	std::string get_param(const std::string& name, 
							const std::string& type, 
							const std::string& value);

	// returns a param where the value is a string:
	// <param name="foo" type="number">1</param>
	std::string get_param(const std::string& name, 
							const std::string& type, 
							int value);

	// returns a modified stringstream with a new param with a string value
	void param(std::stringstream& ss,
				const std::string& name, 
				const std::string& type, 
				const std::string& value);

	// returns a modified stringstream with a new param with an integer value
	void param(std::stringstream& ss,
				const std::string& name, 
				const std::string& type, 
				int value);

	// used in sendToDevice
	std::string get_param_value(const std::string& name, 
								const std::string& val);

}

#endif