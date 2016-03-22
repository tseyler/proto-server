//
// Created by tseyler on 3/21/16.
//

#include <core/protocol/c4soap/c4soap_message.hpp>
#include <gtest/gtest.h>
#include <core/protocol/c4soap/c4soap_getdevicebyinterface.hpp>

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
    EXPECT_EQ( expected_seq, msg.c4soap_seq());
}

TEST_F(C4SoapMessageTest, c4soap_parse_getdevicesbyinterface_test)
{
    std::string c4soap_string = "<c4soap name=\"GetDevicesByInterface\" seq=\"3\" result=\"1\"><devices><id>42</id></devices></c4soap>";
    c4soap_message msg(c4soap_string);
    EXPECT_TRUE(c4soap_getdevicebyinterface::is_response(msg, 3));

    c4soap_getdevicebyinterface response(msg);

    unsigned short expected_id(42);
    EXPECT_EQ( expected_id, response.c4soap_device_id());
}
