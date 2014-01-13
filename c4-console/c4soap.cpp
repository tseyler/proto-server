
#include "c4soap.hpp"


void 
c4soap::begin_c4soap_message(std::stringstream& ss, 
							const std::string& cmd, 
							int& seq, 
							bool async /*= false*/)
{
    ss << "<c4soap name=\"" << cmd << "\" seq=\"" << seq++ <<"\" async=\"";
    ss << (async ? "True" : "False") << "\">";
}

void 
c4soap::end_c4soap_message(std::stringstream& ss)
{
	ss << "</c4soap>";
}

std::string 
c4soap::get_param(const std::string& name, 
					const std::string& type, 
					const std::string& value)
{
    std::stringstream ss;
    ss << "<param name=\"" << name << "\" type=\"" << type << "\">";
    ss << value;
    ss << "</param>";
    
    return ss.str();
}

std::string 
c4soap::get_param(const std::string& name, 
					const std::string& type, 
					int value)
{
    std::stringstream ss;
    ss << "<param name=\"" << name << "\" type=\"" << type << "\">";
    ss << value;
    ss << "</param>";
    
    return ss.str();
}

void 
c4soap::param(std::stringstream& ss,
				const std::string& name, 
				const std::string& type, 
				const std::string& value)
{
	ss << get_param(name, type, value);
}

void 
c4soap::param(std::stringstream& ss,
				const std::string& name, 
				const std::string& type, 
				int value)
{
	ss << get_param(name, type, value);
}

std::string 
c4soap::get_param_value(const std::string& name, 
						const std::string& val)
{
   std::stringstream  ss;
    ss << "<param>";
    ss << "<name>" << name << "</name>";
    ss << "<value type=\"string\">";
    ss << "<static>" << val << "</static>";
    ss << "</value>";
    ss << "</param>";

    return ss.str();
}