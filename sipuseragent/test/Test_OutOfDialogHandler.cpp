
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* Test_OutOfDialogHandler.cpp                                               *
* Copyright (c) 2011, by Control4 Inc.  All rights reserved.	            *
* Created on: Oct 12, 2011													*
* Author: Terry Seyler														*
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#include <test/UnitTest.hpp>
#include "TestReporter.h"
#include "ReportAssert.h"

#include "OutOfDialogHandler.hpp"

using namespace C4UserAgent;

SUITE(Test_OutOfDialogHandler)
{
	class TestOutOfDialogCallback: public IOutOfDialogCallback
	{
	public:

		TestOutOfDialogCallback() : response_(""), result_(oodInit)
		{}

		std::string response_;
		OodResult 	result_;

		void OnResult(OodResult result, const std::string& response, const std::string& /*method*/,
				int /*statusCode*/, const std::string& /*id*/)
		{
			response_ = response;
			result_ = result;
		}
	};

    struct OutOfDialogHandlerFixture
    {
		OutOfDialogHandler* 		handler_;
		TestOutOfDialogCallback*	callback_;
    	resip::ClientOutOfDialogReqHandle h_;
    	resip::ServerOutOfDialogReqHandle s_;
    	resip::SipMessage r_;

    	OutOfDialogHandlerFixture()
        {
			handler_ = new OutOfDialogHandler;
			callback_ = new TestOutOfDialogCallback;
        }

        ~OutOfDialogHandlerFixture()
        {
			delete handler_;
			delete callback_;
        }

        void addOutOfDialogCallback(void)
        {
        	handler_->addCallback(callback_);
        }

    };

    TEST(Initialize_OutOfDialogHandler)
    {
    	OutOfDialogHandler handler;

    	CHECK_EQUAL( oodInit, handler.getResult() );
    }

    TEST_FIXTURE(OutOfDialogHandlerFixture, InitializeTest)
    {
    	//CHECK( !handler_->isRegistered() );
    	CHECK_EQUAL( oodInit, handler_->getResult() );
    	CHECK_EQUAL( 0, handler_->getCollectionSize() );
    }

    TEST_FIXTURE(OutOfDialogHandlerFixture, AddCallbackTest)
    {
    	handler_->addCallback(callback_);
    	CHECK_EQUAL( 1, handler_->getCollectionSize() );
    }

    TEST_FIXTURE(OutOfDialogHandlerFixture, RemoveCallbackTest)
    {
    	addOutOfDialogCallback();
    	handler_->removeCallback(callback_);
    	CHECK_EQUAL( 0, handler_->getCollectionSize() );
    }

    TEST_FIXTURE(OutOfDialogHandlerFixture, OnSuccessTest)
    {
    	addOutOfDialogCallback();
    	handler_->onSuccess(h_, r_);
    	CHECK_EQUAL( oodSuccess, callback_->result_ );
    }

    TEST_FIXTURE(OutOfDialogHandlerFixture, OnFailureTest)
    {
    	addOutOfDialogCallback();
    	handler_->onFailure(h_, r_);
    	CHECK_EQUAL( oodFailure, callback_->result_ );
    }

    TEST_FIXTURE(OutOfDialogHandlerFixture, OnReceivedRequestTest)
    {
    	addOutOfDialogCallback();
    	handler_->onReceivedRequest(s_, r_);
    	CHECK_EQUAL( oodRecvRequest, callback_->result_ );
    }



}
