
#include <string.h>
#include <string>
#include <iostream>
#include <sstream>

#include <UnitTest++.h>
#include <unit_test.h>

#include <http/http_request_handler.hpp>

using namespace proto_http;

TEST(enumerate_method_test)
{
    http_method expected(http_get_method);
    http_method actual = enumerate_method("GET");
    CHECK_EQUAL( expected, actual );
}

TEST(int_to_request_result_test)
{
    http_request_result expected(ok_request);
    http_request_result actual = int_to_request_result(202);
    CHECK_EQUAL( expected, actual );
}

struct test_http_request_handler_fixture
{
    test_http_request_handler_fixture() : get_req_("GET", "/index.html")
	{
	}

    ~test_http_request_handler_fixture()
	{
	}

    http_request_message get_req_;
};

TEST_FIXTURE(test_http_request_handler_fixture, handle_request_test)
{
    http_request_handler req_handler; // we are 200 OK
    http_response_message response;
    http_request_result expected(ok_request);
    http_request_result actual = req_handler.handle_request(get_req_, response);
    CHECK_EQUAL( expected, actual );
}
