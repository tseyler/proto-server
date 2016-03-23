//
// Created by tseyler on 3/21/16.
//

#include <core/protocol/c4soap/c4soap_message.hpp>
#include <gtest/gtest.h>
#include <core/protocol/c4soap/c4soap_getdevicebyinterface.hpp>
#include <core/protocol/c4soap/c4soap_std_getuser.hpp>

using namespace proto_net::protocol::c4soap;


class C4SoapMessageTest : public ::testing::Test
{
protected:

    C4SoapMessageTest()
    {

    }

    ~C4SoapMessageTest()
    {

    }


};

TEST_F(C4SoapMessageTest, c4soap_parse_authenticate_test)
{
    std::string c4soap_string = "<c4soap name=\"AuthenticatePassword\" seq=\"1\" result=\"1\"><success/></c4soap>";
    c4soap_message msg(c4soap_string);

    std::string expected_name("AuthenticatePassword");
    EXPECT_EQ( expected_name, msg.c4soap_name());

    unsigned short expected_seq(1);
    EXPECT_EQ( expected_seq, msg.c4soap_seq() );
}

TEST_F(C4SoapMessageTest, c4soap_node_exists_test)
{
    std::string c4soap_string = "<c4soap name=\"AuthenticatePassword\" seq=\"1\" result=\"1\"><success/></c4soap>";
    c4soap_message msg(c4soap_string);

    EXPECT_TRUE( msg.node_exists("c4soap.success") );
}

TEST_F(C4SoapMessageTest, c4soap_parse_getdevicesbyinterface_test)
{
    std::string c4soap_string = "<c4soap name=\"GetDevicesByInterface\" seq=\"3\" result=\"1\"><devices><id>42</id></devices></c4soap>";
    c4soap_message msg(c4soap_string);
    EXPECT_TRUE(c4soap_getdevicebyinterface::is_response(msg, 3));

    c4soap_getdevicebyinterface response(msg);

    unsigned short expected_id(42);
    EXPECT_EQ( expected_id, response.c4soap_device_id() );
}

TEST_F(C4SoapMessageTest, c4soap_parse_getuser_test)
{
    std::string c4soap_string = "<c4soap name=\"SendToDevice\" seq=\"11\" result=\"1\"><device><deviceId>62</deviceId><key>000FFF5053CF@192.168.1.18</key><user>000FFF5053CF</user><intercomname>Room`Portable_7_Touch_Screen_V2</intercomname><domain>192.168.1.18</domain><realm>192.168.1.18</realm><password>65457de5529bee5c2b7941a63f2da0bd</password><name>Portable 7\" Touch Screen V2</name><email/><forwardAddress/><room>Room</room><state>1</state><isDoorStation>False</isDoorStation></device></c4soap>";
    c4soap_message msg(c4soap_string);
    c4soap_sendtodevice std_msg(msg, "getUser");
    c4soap_std_getuser response(std_msg);

    EXPECT_TRUE(c4soap_std_getuser::is_response(response, 11));

    unsigned short expected_id(62);
    EXPECT_EQ( expected_id, response.c4soap_device_id() );

    std::string expected_user("000FFF5053CF");
    EXPECT_EQ( expected_user, response.c4soap_user() );

    std::string expected_domain("192.168.1.18");
    EXPECT_EQ( expected_domain, response.c4soap_domain() );

    std::string expected_password("65457de5529bee5c2b7941a63f2da0bd");
    EXPECT_EQ( expected_password, response.c4soap_password() );
}
