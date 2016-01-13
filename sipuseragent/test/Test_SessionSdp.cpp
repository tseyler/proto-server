
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* Test_SessionSdp.cpp                                               		*
* Copyright (c) 2011, by Control4 Inc.  All rights reserved.	            *
* Created on: Oct 25, 2011													*
* Author: Terry Seyler														*
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#include <test/UnitTest.hpp>
#include "TestReporter.h"
#include "ReportAssert.h"

#include <sstream>

#include "userAgentHelper.h"
#include "SessionSdp.hpp"

using namespace resip;
using namespace C4UserAgent;

SUITE(Test_SessionSdp)
{
	Data c4Data("v=0\r\n"
						"o=1900 0 0 IN IP4 10.11.101.87\r\n"
						"s=Control4 User Agent\r\n"
						"c=IN IP4 10.11.101.87\r\n"
						"t=0 0\r\n"
						"m=audio 54874 RTP/AVP 96 97 0 8\r\n"
						"a=rtpmap:96 PCMU-WB/16000\r\n"
						"a=rtpmap:97 PCMA-WB/16000\r\n"
						"a=rtpmap:0 PCMU/8000\r\n"
						"a=rtpmap:8 PCMA/8000\r\n"
						"a=sendrecv\r\n"
						);

    Data xliteData("v=0\r\n"
					 "o=MxSIP1 0 0 IN IP4 192.168.2.15\r\n"
					 "s=BCM_Doorstion_Call\r\n"
					 "c=IN IP4 192.168.2.15\r\n"
					 "t=0 0\r\n"
					 "m=audio 8000 RTP/AVP 8 3 98 97 101\r\n"
					 "a=rtpmap:8 pcma/8000\r\n"
					 "a=rtpmap:3 gsm/8000\r\n"
					 "a=rtpmap:98 iLBC\r\n"
					 "a=rtpmap:97 speex/8000\r\n"
					 "a=rtpmap:101 telephone-event/8000\r\n"
					 "a=fmtp:101 0-15\r\n"
					);

	Data doorStationSDP("v=0\r\n"
					 "o=1900 369696545 369696545 IN IP4 192.168.2.15\r\n"
					 "s=X-Lite\r\n"
					 "c=IN IP4 224.2.2.2/1\r\n"
					 "t=0 0\r\n"
					 "m=video 4000 RTP/AVP 120\r\n"
					 "c=IN IP4 224.2.2.2/1\r\n"
					 "a=rtpmap:120 H264/90000\r\n"
					 "m=audio 8000 RTP/AVP 8 3 98 97 101\r\n"
					 "c=IN IP4 224.2.2.2/1\r\n"
					 "a=rtpmap:8 pcma/8000\r\n"
					 "a=rtpmap:3 gsm/8000\r\n"
					 "a=rtpmap:98 iLBC\r\n"
					 "a=rtpmap:97 speex/8000\r\n"
					 "a=rtpmap:101 telephone-event/8000\r\n"
					 "a=fmtp:101 0-15\r\n"
					);

	Data badSDP("v=0\r\n"
						"o=1900 0 0 IN IP4 10.11.101.87\r\n"
						"s=Bad SDP\r\n"
						"c=IN IP4 10.11.101.87\r\n"
						"t=0 0\r\n"
						"m=audio 54874 RTP/AVP 96 97 0 8\r\n"
						"a=rtpmap:96 PCMU-WB/16000\r\n"
						"a=rtpmap:97 PCMA-WB/16000\r\n"
						"a=rtpmap:PCMU/8000\r\n"
						"a=rtpmap:8 PCMA/8000\r\n"
						"a=sendrecv\r\n"
						);

    struct SessionSdpFixture
    {
    	SessionSdpFixture()
        {
    		hfv_ = new HeaderFieldValue(c4Data.data(), static_cast<unsigned int>(c4Data.size()));
    		Mime type("application", "sdp");
    		sdp_ = new SdpContents(hfv_, type);
    		sessionSdp_ = new SessionSdp(sdp_);
        }

        ~SessionSdpFixture()
        {
        	delete hfv_;
        	delete sdp_;
			delete sessionSdp_;
        }

        HeaderFieldValue* hfv_;
        SdpContents* sdp_;
        SessionSdp* sessionSdp_;
    };

    TEST(Initialize_SessionSdp)
    {
		HeaderFieldValue hfv = HeaderFieldValue(c4Data.data(), static_cast<unsigned int>(c4Data.size()));
		Mime type("application", "sdp");
		SdpContents sdp(&hfv, type);
    	SessionSdp* sessionSdp = new SessionSdp(&sdp);
    	CHECK_EQUAL( 0, sessionSdp->getSdpVersion() );

    	delete sessionSdp;
    }

    TEST_FIXTURE(SessionSdpFixture, InitializeTest)
    {
    	CHECK_EQUAL( 0, sessionSdp_->getSdpVersion() );
    	std::string expected = "Control4 User Agent";
    	CHECK_EQUAL( expected, sessionSdp_->getSessionName() );
    }

    TEST_FIXTURE(SessionSdpFixture, ConnectionAddressTest)
    {
    	std::string expected = "10.11.101.87";
    	SessionSdp::SdpConnection connection = sessionSdp_->getConnection();
    	CHECK_EQUAL( expected, connection.getAddress() );
    }

    TEST_FIXTURE(SessionSdpFixture, MediaNameTest)
    {
    	std::string expected = "audio";
    	SessionSdp::SdpMedia* sdpMedia = sessionSdp_->getFrontMedia();
    	CHECK_EQUAL( expected, sdpMedia->getName() );
    }

    TEST_FIXTURE(SessionSdpFixture, MediaPortTest)
    {
    	int expected = 54874;
    	SessionSdp::SdpMedia* sdpMedia = sessionSdp_->getFrontMedia();
    	CHECK_EQUAL( expected, sdpMedia->getPort() );
    }

    TEST_FIXTURE(SessionSdpFixture, MediaMulticastTest)
    {
    	int expected = 1;
    	SessionSdp::SdpMedia* sdpMedia = sessionSdp_->getFrontMedia();
    	CHECK_EQUAL( expected, sdpMedia->getMulticast() );
    }

    TEST_FIXTURE(SessionSdpFixture, MediaProtocolTest)
    {
    	std::string expected = "RTP/AVP";
    	SessionSdp::SdpMedia* sdpMedia = sessionSdp_->getFrontMedia();
    	CHECK_EQUAL( expected, sdpMedia->getProtocol() );
    }

    TEST_FIXTURE(SessionSdpFixture, MediaFormatsTest)
    {
    	size_t expected = 4;
    	SessionSdp::SdpMedia* sdpMedia = sessionSdp_->getFrontMedia();
    	CHECK_EQUAL( expected, sdpMedia->getFormats().size() );
    }

    TEST_FIXTURE(SessionSdpFixture, MediaNegotiateFormatsTest)
    {
    	HeaderFieldValue hfv = HeaderFieldValue(xliteData.data(), static_cast<unsigned int>(xliteData.size()));
    	Mime type("application", "sdp");
    	SdpContents sdp(&hfv, type);
    	SessionSdp sdpRemote(&sdp);
    	SessionSdp::SdpMedia* sdpRemoteMedia = sdpRemote.getFrontMedia();

    	int expected = 8;
    	SessionSdp::SdpMedia* sdpLocalMedia = sessionSdp_->getFrontMedia();
		SdpFormatCollection codecs = sdpLocalMedia->negotiateFormats(*sdpRemoteMedia);
		SdpFormatIterator it = codecs.begin();

    	CHECK_EQUAL( expected, *it );
    }

    TEST_FIXTURE(SessionSdpFixture, MediaPrimaryFormatTest)
    {
//    	HeaderFieldValue hfv = HeaderFieldValue(xliteData.data(), static_cast<unsigned int>(xliteData.size()));
//    	Mime type("application", "sdp");
//    	SdpContents sdp(&hfv, type);
//    	SessionSdp sdpRemote(&sdp);
//    	SessionSdp::SdpMedia* sdpRemoteMedia = sdpRemote.getFrontMedia();

    	int expected = 96;
    	SessionSdp::SdpMedia* sdpLocalMedia = sessionSdp_->getFrontMedia();

    	CHECK_EQUAL( expected, sdpLocalMedia->primaryFormat() );
    }

    TEST_FIXTURE(SessionSdpFixture, ConnectionToStringTest)
    {
    	SessionSdp::SdpConnection connection = sessionSdp_->getConnection();
    	std::string expected = "c=IN IP4 10.11.101.87\r\n";

    	CHECK_EQUAL( expected, connection.toString() );
    }

    TEST_FIXTURE(SessionSdpFixture, OriginToStringTest)
    {
    	SessionSdp::SdpOrigin origin = sessionSdp_->getOrigin();
    	std::string expected = "o=1900 0 0 IN IP4 10.11.101.87\r\n";

    	CHECK_EQUAL( expected, origin.toString() );
    }

    TEST_FIXTURE(SessionSdpFixture, TimeToStringTest)
    {
    	SessionSdp::SdpTime* time = sessionSdp_->getFrontTime();
    	std::string expected = "t=0 0\r\n";

    	CHECK_EQUAL( expected, time->toString() );
    }

    TEST_FIXTURE(SessionSdpFixture, MediaToStringTest)
    {
    	SessionSdp::SdpMedia* media = sessionSdp_->getFrontMedia();
    	std::string expected = "m=audio 54874 RTP/AVP 96 97 0 8\r\n";

    	CHECK_EQUAL( expected, media->toString() );
    }

    TEST_FIXTURE(SessionSdpFixture, RtpMapToStringTest)
    {
    	std::stringstream ss;

    	ss << "a=rtpmap:96 PCMU-WB/16000\r\n";
    	ss << "a=rtpmap:97 PCMA-WB/16000\r\n";
    	ss << "a=rtpmap:0 PCMU/8000\r\n";
    	ss << "a=rtpmap:8 PCMA/8000\r\n";

    	std::string expected = ss.str();

    	SessionSdp::SdpMedia* media = sessionSdp_->getFrontMedia();

    	CHECK_EQUAL( expected, media->rtpMapToString() );
    }

    TEST_FIXTURE(SessionSdpFixture, SessionSdpToStringTest)
    {
    	std::stringstream ss;

    	ss << "v=0\r\n";
    	ss << "o=1900 0 0 IN IP4 10.11.101.87\r\n";
    	ss << "s=Control4 User Agent\r\n";
    	ss << "c=IN IP4 10.11.101.87\r\n";
    	ss << "t=0 0\r\n";
    	ss << "m=audio 54874 RTP/AVP 96 97 0 8\r\n";
    	ss << "a=rtpmap:96 PCMU-WB/16000\r\n";
    	ss << "a=rtpmap:97 PCMA-WB/16000\r\n";
    	ss << "a=rtpmap:0 PCMU/8000\r\n";
    	ss << "a=rtpmap:8 PCMA/8000\r\n";
    	ss << "a=sendrecv\r\n";

    	std::string expected = ss.str();

    	CHECK_EQUAL( expected,  sessionSdp_->toString() );
    }

    TEST_FIXTURE(SessionSdpFixture, ToSdpContentTest)
    {
    	int expectedVersion = 0;
    	std::string expectedName = "Control4 User Agent";

    	SdpContents sdp = sessionSdp_->toSdpContents();
    	SdpContents::Session session = sdp.session();
    	int sdpVersion = session.version();
    	std::string sessionName = C4UserAgent::makeString(session.name());
    	CHECK_EQUAL( expectedVersion, sdpVersion );
    	CHECK_EQUAL( expectedName, sessionName );
    }

    TEST_FIXTURE(SessionSdpFixture, CopySessionSdpTest)
    {
    	SessionSdp sessionSdp = *sessionSdp_;

    	CHECK_EQUAL( 0, sessionSdp.getSdpVersion() );
    	std::string expected = "Control4 User Agent";
    	CHECK_EQUAL( expected, sessionSdp.getSessionName() );
    }

    TEST_FIXTURE(SessionSdpFixture, AndFormatTest)
    {
    	HeaderFieldValue hfv = HeaderFieldValue(xliteData.data(), static_cast<unsigned int>(xliteData.size()));
    	Mime type("application", "sdp");
    	SdpContents sdp(&hfv, type);
    	SessionSdp sdpRemote(&sdp);
    	SessionSdp::SdpMedia* sdpRemoteMedia = sdpRemote.getFrontMedia();
        SessionSdp::SdpMedia* sdpMedia = sessionSdp_->getFrontMedia();
        sdpMedia->andFormats(*sdpRemoteMedia);

       	size_t expected = 2;
    	CHECK_EQUAL( expected, sdpMedia->getFormats().size() );
    }

    TEST_FIXTURE(SessionSdpFixture, MediaTypeTest)
    {
        SessionSdp::SdpMedia* sdpMedia = sessionSdp_->getFrontMedia();

        SessionSdp::SdpMedia::MediaType expected = SessionSdp::SdpMedia::mediaAudio;
    	CHECK_EQUAL( expected, sdpMedia->getMediaType() );
    }

    TEST_FIXTURE(SessionSdpFixture, AddRtpMapContainerTest)
    {
    	HeaderFieldValue hfv = HeaderFieldValue(badSDP.data(), static_cast<unsigned int>(badSDP.size()));
    	Mime type("application", "sdp");
    	SdpContents sdp(&hfv, type);

    	SdpContents::Session session = sdp.session();
    	SdpContents::Session::MediumContainer mediaContainer = session.media();
    	SdpContents::Session::MediumContainer::iterator mit = mediaContainer.begin();
    	SdpContents::Session::Medium media = *mit;
    	std::string mediaName = C4UserAgent::makeString(media.name());
    	int mediaPort = media.port();
    	int mediaMulticast = media.multicast();
    	std::string mediaProtocol = C4UserAgent::makeString(media.protocol());
    	SessionSdp::SdpMedia sdpMedia(mediaName, mediaPort, mediaMulticast, mediaProtocol);

    	sdpMedia.addRtpMapContainer(media);

    	size_t expected = 3;
    	CHECK_EQUAL( expected, sdpMedia.getRtpMap().size());
    }

	TEST_FIXTURE(SessionSdpFixture, MulticastConnectionTest)
    {
    	HeaderFieldValue hfv = HeaderFieldValue(doorStationSDP.data(), static_cast<unsigned int>(doorStationSDP.size()));
    	Mime type("application", "sdp");
    	SdpContents sdp(&hfv, type);

    	SessionSdp sessionDoorStation(&sdp);

		unsigned long expected = 1;
		unsigned long actual = sessionDoorStation.getConnection().getTtl();

    	CHECK_EQUAL( expected, actual );
	}

	TEST_FIXTURE(SessionSdpFixture, MediaConnectionTest)
	{
    	HeaderFieldValue hfv = HeaderFieldValue(doorStationSDP.data(), static_cast<unsigned int>(doorStationSDP.size()));
    	Mime type("application", "sdp");
    	SdpContents sdp(&hfv, type);

    	SessionSdp sessionDoorStation(&sdp);

		std::string expected = "224.2.2.2";

		SessionSdp::SdpMedia* sdp_media = sessionDoorStation.getFrontMedia();
		while (sdp_media)
		{
			SessionSdp::SdpConnection* connection = sdp_media->getFrontConnection();
			if (connection)
			{
				std::string actual = connection->getAddress();
				CHECK_EQUAL( expected, actual );
			}

			sdp_media = sessionDoorStation.getNextMedia(sdp_media);
		}
	}
}
