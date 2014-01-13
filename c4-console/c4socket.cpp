

#include "c4socket.hpp"

size_t 
c4socket::write_msg(tcp::socket& s, const std::string& msg)
{
    char buf[1024];
    memset(buf, 0, 1024);
    memcpy(buf, msg.c_str(), msg.length());
 
    return boost::asio::write(s, boost::asio::buffer(buf, strlen(buf) + 1));
}

std::string 
c4socket::read_msg(tcp::socket& s)
{
    char buf[4096];
    memset(buf, 0, 4096);
    boost::asio::streambuf b;
    if (boost::asio::read_until(s, b, '\0'))
    {
		std::istream is(&b);
		is.get(buf, 4096, '\0');
    }

    return std::string(buf);
}