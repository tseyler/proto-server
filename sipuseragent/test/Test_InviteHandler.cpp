
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* Test_InviteHandler.cpp                                              		*
* Copyright (c) 2011, by Control4 Inc.  All rights reserved.	            *
* Created on: Oct 12, 2011													*
* Author: Terry Seyler														*
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

//#include <memory>
#include <test/UnitTest.hpp>
#include "TestReporter.h"
#include "ReportAssert.h"

#include "sip/resip_dum.h"
#include "sip/resip_dum_ssl.h"
#include "sip/resip_stack.h"
#include "sip/resip_stack_ssl.h"
#include "sip/rutil.h"

#include "InviteHandler.hpp"

using namespace C4UserAgent;

SUITE(Test_InviteHandler)
{

	class TestInviteCallback: public IInviteCallback
	{
	public:

		TestInviteCallback() : response_(""), result_(inviteInit)
		{}

		std::string response_;
		InviteResult 	result_;

		void OnResult(InviteResult result, const std::string& response,
				const std::string& /*method*/, int /*statusCode*/, const std::string& /*id*/)
		{
			response_ = response;
			result_ = result;
		}
	};

    struct InviteHandlerFixture
    {
		std::auto_ptr<InviteHandler> 		handler_;
		std::auto_ptr<TestInviteCallback>	callback_;

    	InviteHandlerFixture() : handler_(new InviteHandler), callback_(new TestInviteCallback)
        { }

        ~InviteHandlerFixture()
        { }

        void addInviteCallback(void)
        {
        	handler_->addCallback(callback_.get());
        }

    };

    TEST(Initialize_InviteHandler)
    {
    	InviteHandler handler;

    	CHECK_EQUAL( inviteInit, handler.getResult() );
    }

    TEST_FIXTURE(InviteHandlerFixture, InitializeTest)
    {
    	CHECK_EQUAL( inviteInit, handler_->getResult() );
    	CHECK_EQUAL( 0, handler_->getCollectionSize() );
    }

    TEST_FIXTURE(InviteHandlerFixture, AddCallbackTest)
    {
    	handler_->addCallback(callback_.get());
    	CHECK_EQUAL( 1, handler_->getCollectionSize() );
    }

    TEST_FIXTURE(InviteHandlerFixture, RemoveCallbackTest)
    {
    	addInviteCallback();
    	handler_->removeCallback(callback_.get());
    	CHECK_EQUAL( 0, handler_->getCollectionSize() );
    }

    TEST_FIXTURE(InviteHandlerFixture, OnNewClientSessionTest)
    {
    	addInviteCallback();
    	handler_->setResult(inviteClientSuccess);
    	handler_->fireResult("inviteClientSuccess", "INVITE", 200);
    	CHECK_EQUAL( inviteClientSuccess, callback_->result_ );
    }

    TEST_FIXTURE(InviteHandlerFixture, OnNewServerSessionTest)
    {
    	addInviteCallback();
    	handler_->setResult(inviteServerSuccess);
    	handler_->fireResult("inviteServerSuccess", "INVITE", 200);
    	CHECK_EQUAL( inviteServerSuccess, callback_->result_ );
    }

    TEST_FIXTURE(InviteHandlerFixture, OnFailureTest)
    {
    	addInviteCallback();
    	handler_->setResult(inviteFailure);
    	handler_->fireResult("inviteFailure", "INVITE", 200);
        CHECK_EQUAL( inviteFailure, callback_->result_ );
    }

    TEST_FIXTURE(InviteHandlerFixture, OnConnectedClientTest)
    {
    	addInviteCallback();
    	handler_->setResult(inviteConnected);
    	handler_->fireResult("inviteConnected", "INVITE", 200);
    	CHECK_EQUAL( inviteConnected, callback_->result_ );
    }

     TEST_FIXTURE(InviteHandlerFixture, OnTerminatedTest)
    {
    	addInviteCallback();
      	handler_->setResult(inviteTerminated);
        handler_->fireResult("inviteTerminated", "INVITE", 200);
    	CHECK_EQUAL( inviteTerminated, callback_->result_ );
    }

}
