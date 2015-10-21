//
// Created by Terry Seyler on 10/15/15.
//

#include "echo_server.hpp"



echo_server::echo_server(unsigned short port_num /*= 9669*/) : proto_tcp_server(port_num)
{

}

// copy constructor
echo_server::echo_server(const echo_server& es)
{

}

echo_server::~echo_server()
{

}

echo_server&
echo_server::clone(const echo_server& ps)
{
    //proto_tcp_server::clone(dynamic_cast<const proto_tcp_server&>(ps));

    return *this;
}

echo_server&
echo_server::operator =(const echo_server& ps)
{
    return clone(ps);
}

void
echo_server::ps_initialize(void)
{

}
void
echo_server::ps_run(void)
{

}

void
echo_server::ps_io(const proto_net_data& req_data, proto_net_data& res_data)
{

}

//void
//echo_server::ps_start_accept(void)
//{
//
//}

