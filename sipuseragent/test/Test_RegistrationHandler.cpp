
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* Test_RegistrationHandler.cpp                                              *
* Copyright (c) 2011, by Control4 Inc.  All rights reserved.	            *
* Created on: Oct 12, 2011													*
* Author: Terry Seyler														*
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#include <test/UnitTest.hpp>
#include "TestReporter.h"
#include "ReportAssert.h"

#include "RegistrationHandler.hpp"

using namespace C4UserAgent;

SUITE(Test_RegistrationHandler)
{
	class TestRegistrationCallback: public IRegistrationCallback
	{
	public:

		TestRegistrationCallback() : response_(""), result_(regInit)
		{}

		std::string response_;
		RegResult 	result_;

		void OnResult(RegResult result, const std::string& response, const std::string& /*method*/,
				int /*statusCode*/, const std::string& /*id*/)
		{
			response_ = response;
			result_ = result;
		}
	};

    struct RegistrationHandlerFixture
    {
    	RegistrationHandler* 		handler_;
    	TestRegistrationCallback*	callback_;
    	resip::ClientRegistrationHandle h_;
    	resip::SipMessage r_;

    	RegistrationHandlerFixture()
        {
			handler_ = new RegistrationHandler;
			callback_ = new TestRegistrationCallback;
        }

        ~RegistrationHandlerFixture()
        {
			delete handler_;
			delete callback_;
        }

        void addRegistrationCallback(void)
        {
        	handler_->addCallback(callback_);
        }

    };

    TEST(Initialize_RegistrationHandler)
    {
    	RegistrationHandler handler;

    	CHECK_EQUAL( regInit, handler.getResult() );
    }

    TEST_FIXTURE(RegistrationHandlerFixture, InitializeTest)
    {
    	CHECK( !handler_->isRegistered() );
    	CHECK_EQUAL( regInit, handler_->getResult() );
    	CHECK_EQUAL( 0, handler_->getCollectionSize() );
    }

    TEST_FIXTURE(RegistrationHandlerFixture, AddCallbackTest)
    {
    	handler_->addCallback(callback_);
    	CHECK_EQUAL( 1, handler_->getCollectionSize() );
    }

    TEST_FIXTURE(RegistrationHandlerFixture, RemoveCallbackTest)
    {
    	addRegistrationCallback();
    	handler_->removeCallback(callback_);
    	CHECK_EQUAL( 0, handler_->getCollectionSize() );
    }

    TEST_FIXTURE(RegistrationHandlerFixture, OnSuccessTest)
    {
    	addRegistrationCallback();
    	handler_->onSuccess(h_, r_);
    	CHECK_EQUAL( regSuccess, callback_->result_ );
    }

    TEST_FIXTURE(RegistrationHandlerFixture, OnRemovedTest)
    {
    	addRegistrationCallback();
    	handler_->onRemoved(h_, r_);
    	CHECK_EQUAL( regRemoved, callback_->result_ );
    }

    TEST_FIXTURE(RegistrationHandlerFixture, OnFailureTest)
    {
    	addRegistrationCallback();
    	handler_->onFailure(h_, r_);
    	CHECK_EQUAL( regFailure, callback_->result_ );
    }

    TEST_FIXTURE(RegistrationHandlerFixture, OnRequestRetryTest)
    {
    	addRegistrationCallback();
    	handler_->onRequestRetry(h_, 1, r_);
    	CHECK_EQUAL( regRetry, callback_->result_ );
    }



}
