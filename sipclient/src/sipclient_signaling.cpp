

#include "sipclient_signaling.hpp"
#include "sipclient_layer_event.hpp"

using namespace resip;
using namespace SipUserAgent;

#define __CLASS__ "sipclient_signaling"

namespace sipclient
{
	sipclient_signaling::sipclient_signaling(const std::string& local_address, const std::string& profile,
											 sipclient_logger_ptr logger_ptr,
											 sipclient_notification_ptr notification_ptr) :
	local_address_(local_address),
	user_agent_(new UserAgent("sipclient")),
	registered_(false),
	profile_aor_(profile),
	logger_ptr_(logger_ptr),
	notification_ptr_(notification_ptr)
    {
    	setup_local_SDP();
    }

	sipclient_signaling::~sipclient_signaling()
    {}

	void
	sipclient_signaling::sipclient_log_msg(const std::string& class_name, const std::string& function_name,
										   int line, const std::string& log_msg)
	{
		if (logger_ptr_)
			logger_ptr_->sipclient_log(class_name, function_name, line, log_msg);
	}

	void
	sipclient_signaling::sipclient_log_msg(const std::string& class_name, const std::string& function_name, int line,
						   const std::stringstream& log_stream)
	{
		if (logger_ptr_)
			logger_ptr_->sipclient_log(class_name, function_name, line, log_stream);
	}

	void
	sipclient_signaling::sipclient_notify(layer_sipclient layer, unsigned short layer_event,
								  const std::string& class_name, const std::string& function_name,
								  int line, const std::string& notify_msg)
	{
		if (notification_ptr_)
			notification_ptr_->sipclient_notify(layer, layer_event, __CLASS__, __FUNCTION__, __LINE__, notify_msg);
	}

	void
	sipclient_signaling::sipclient_notify(layer_sipclient layer, unsigned short layer_event,
								  const std::string& class_name, const std::string& function_name,
								  int line, const std::stringstream& notify_stream)
	{
		if (notification_ptr_)
			notification_ptr_->sipclient_notify(layer, layer_event, __CLASS__, __FUNCTION__, __LINE__, notify_stream);
	}

    bool 
    sipclient_signaling::is_forking(void)
    {
		SipMessage msg = invite_handler_->getMessage();
		Data to_hfv = Data::from(msg.header(h_To));
		std::string to_str = makeString(to_hfv);
		std::size_t found = to_str.find("Forking");

		return bool(found != std::string::npos);
    }

    void 
    sipclient_signaling::OnResult(RegResult reg_result,
				  const std::string& reg_response, 
				  const std::string& method_string, 
				  int status_code, 
				  const std::string& call_id)
    {
		// notify waiting threads
		condition_.notify_one();

		switch (reg_result)
		{
		case regSuccess:

			registered_ = true;
			sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, "reg_result = regSuccess");
			break;
		case regRemoved:

			sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, "reg_result = regRemoved");
			break;
		case regFailure:

			sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, "reg_result = regFailure");
			break;
		case regRetry:

			sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, "reg_result = regRetry");
			break;
		case regInit:

			sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, "reg_result = regInit");
			break;
		default:

			break;
		}
    }

    void 
    sipclient_signaling::OnResult(InviteResult invite_result,
				  const std::string& invite_response, 
				  const std::string& method_string, 
				  int status_code, 
				  const std::string& call_id)
    {
		std::stringstream log_stream;
		log_stream << invite_response << "; Call ID = " << call_id;
		sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, log_stream);

		switch (invite_result)
		{
		case inviteClientSuccess:

			sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, "invite_result = inviteClientSuccess");
			break;
		// Was called (invited) by another device.
		case inviteServerSuccess:

			sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, "invite_result = inviteServerSuccess");
			break;
		case inviteFailure:

			sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, "invite_result = inviteFailure");
			break;
		case inviteAnswer:

			sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, "invite_result = inviteAnswer");
			break;
		case inviteConnected:

			sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, "invite_result = inviteConnected");
			break;
		case inviteTerminated:

			sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, "invite_result = inviteTerminated");
			break;
		case inviteOffer:

			sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, "invite_result = inviteOffer");
			break;
		case inviteOfferRequired:

			sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, "invite_result = inviteOfferRequired");
			break;
		case inviteEarlyMedia:

			sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, "invite_result = inviteEarlyMedia");
			break;
		case inviteProvisional:

			sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, "invite_result = inviteProvisional");
			break;
		case inviteMessageSuccess:

			sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, "invite_result = inviteMessageSuccess");
			break;
		case inviteMessageFailure:

			sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, "invite_result = inviteMessageFailure");
			break;
		case inviteMessageReceived:

			sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, "invite_result = inviteMessageReceived");
			break;
		default:

			break;
		}
    }

    void 
    sipclient_signaling::OnSessionChanged(SessionStatus ss, SessionDialog* dialog)
    {
		if (!dialog)
			return;

		unsigned long  session_id = dialog->get_session_id();
		std::stringstream log_stream;

		//ServerInviteSession
		resip::InviteSession* invite_session = dialog->getInviteSession();

		if (invite_session)
		{
			switch (ss)
			{
			case sNewSession:

				call_id_ = dialog->getCallId();

				log_stream <<  "SessionStatus = sNewSession; Call ID = " << call_id_ << "; Session ID = " << session_id;
				sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, log_stream);
			break;
			case sAnswer:

				log_stream <<  "SessionStatus = sAnswer Call ID = " << call_id_ << "; Session ID = " << session_id;
				sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, log_stream);
			break;
			case sOffer:
			{
				resip::ServerInviteSession* server_invite_session = dynamic_cast<resip::ServerInviteSession*>(invite_session);

				if (server_invite_session) // we have an incoming call
				{
					// get the remote's SDP
					SessionSdpPtr remote_sdp = dialog->getRemoteSdp();
					if (remote_sdp) // we have remote SDP
					{
						std::string remote_sdp_str = remote_sdp->toString();
						std::cout << "Remote SDP:" << std::endl << remote_sdp_str << std::endl;

						// make a copy of the local SDP
						SessionSdpPtr session_sdp(new SessionSdp(local_sdp_));
						// negotiate the media
						session_sdp->negotiateMedia(remote_sdp);

						std::string local_sdp_str = local_sdp_.toString();
						std::cout << "Local SDP:" << std::endl << local_sdp_str << std::endl;
						//SessionSdp::SdpConnection connection = remote_sdp->getConnection();
						//bool multicast = (connection.getTtl());//connection.is_multicast_address();
						//bool forking = is_forking();
						int provisional_code(180);
						//if (forking && multicast)
						//{
						//	session_sdp.setSdpConnection(connection.getAddress(), 1);
						//	provisional_code = 183; // provisional progress
						//}

						server_invite_session->provisional(provisional_code); // putting this before provideAnswer
						invite_session->provideAnswer(session_sdp->toSdpContents());
						//server_invite_session->provisional(provisional_code); // restore after 2.7.2
						// experimental
						//resip::SipMessage msg = invite_handler_->getMessage();
						//	const resip::HeaderFieldValueList* hfv_list = msg.getRawHeader(Headers::To);
						//	resip::HeaderFieldValueList::const_iterator it = hfv_list->begin();
						//	while (it != hfv_list->end())
						//	{
						//		resip::HeaderFieldValue* hfv = *it;

						//	}
						//SessionSdp* remote_sdp = dialog->getRemoteSdp();
						//std::string session_name = remote_sdp->getSessionName();
						//std::string remote_user = dialog->getRemoteUser();
						//std::cout << "sipclient_signaling::OnSessionChanged: Remote User = " << remote_user << "; Session Name = " << session_name << std::endl;

						//std::string sdp_remote = dialog->getRemoteSdp()->toString();
						//std::cout << "sipclient_signaling::OnSessionChanged: Remote SDP = " << sdp_remote << std::endl;
						//SdpContents sdp_contents;
						//setup_local_SDP(sdp_contents);
						//dialog->setSessionSdp(new SessionSdp(&sdp_contents));
						// experimental
					}
				}
			}
				log_stream <<  "SessionStatus = sOffer; Call ID = " << dialog->getCallId() << "; Session ID = " << session_id;
				sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, log_stream);
				break;
			case sEarlyMedia:

				log_stream <<  "SessionStatus = sEarlyMedia; Call ID = " << dialog->getCallId() << "; Session ID = " << session_id;
				sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, log_stream);
				break;
			case sTerminated:

				log_stream <<  "SessionStatus = sTerminated; Call ID = " << dialog->getCallId() << "; Session ID = " << session_id;
				sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, log_stream);
			break;
			case sOfferRequired:

				log_stream <<  "SessionStatus = sOfferRequired; Call ID = " << dialog->getCallId() << "; Session ID = " << session_id;
				sipclient_log_msg(__CLASS__, __FUNCTION__, __LINE__, log_stream);
				break;
			default:

			break;
			}
		}
    }

    void 
    sipclient_signaling::init(void)
    {
		reg_handler_ = user_agent_->getRegistrationHandler();
		reg_handler_->addCallback(this);

		invite_handler_ = user_agent_->getInviteHandler();
		invite_handler_->addCallback(this);
		invite_handler_->addSessionCallback(this);

		// set supported method PRACK
		user_agent_->setSupportedMethod(resip::PRACK, resip::Mime("application", "pidf+xml"));
		// set supported method INVITE
		user_agent_->setSupportedMethod(resip::INVITE, resip::Mime("application", "pidf+xml"));
		// set supported method ACK
		user_agent_->setSupportedMethod(resip::ACK, resip::Mime("application", "pidf+xml"));
		// set supported method BYE
		user_agent_->setSupportedMethod(resip::BYE, resip::Mime("application", "pidf+xml"));
		// set supported method CANCEL
		user_agent_->setSupportedMethod(resip::CANCEL, resip::Mime("application", "pidf+xml"));
		// set supported method UPDATE
		user_agent_->setSupportedMethod(resip::UPDATE, resip::Mime("application", "pidf+xml"));
		// set supported method NOTIFY
		user_agent_->setSupportedMethod(resip::NOTIFY, resip::Mime("application", "pidf+xml"));
		// set supported method SUBSCRIBE
		user_agent_->setSupportedMethod(resip::SUBSCRIBE, resip::Mime("application", "pidf+xml"));
		// set supported method PUBLISH
		user_agent_->setSupportedMethod(resip::PUBLISH, resip::Mime("application", "pidf+xml"));
		// set supported method MESSAGE
		//ua.setSupportedMethod(resip::MESSAGE, resip::Mime("application", "im-iscomposing+xml"));
		user_agent_->setSupportedMethod(resip::MESSAGE, resip::Mime("text", "plain"));
		//ua.setSupportedMethod(resip::MESSAGE, resip::Mime("text", "html"));

		// set supported method REFER
		user_agent_->setSupportedMethod(resip::REFER, resip::Mime("application", "pidf+xml"));
		// set supported method INFO
		user_agent_->setSupportedMethod(resip::INFO, resip::Mime("application", "pidf+xml"));

		// add other supported methods
		user_agent_->setSupportedMethod(resip::REGISTER, resip::Mime("application", "pidf+xml"));
		user_agent_->setSupportedMethod(resip::RESPONSE, resip::Mime("application", "pidf+xml"));
		user_agent_->setSupportedMethod(resip::SERVICE, resip::Mime("application", "pidf+xml"));
    }

    std::string
    sipclient_signaling::set_profile_aor(const std::string& display_name,
					 const std::string& user_name, 
					 const std::string& proxy_ip)
    {
		// Create the aor string with display name and address.
		return "\"" + display_name + "\" " + "<sip:" + user_name + "@" + proxy_ip + ":5060>";
    }

    void 
    sipclient_signaling::register_useragent(void)
    {
		// Setup a new local authManager, registration fails if we don't re-init the authManager
		// every time before setting it in UserAgent.
		std::auto_ptr<ClientAuthManager> auth_manager(new ClientAuthManager);
		user_agent_->setAuthenticationManager(auth_manager);

		// Registration time.
		user_agent_->setRegistrationTime(SIP_REG_TIME);

		// Set registration retry time.
		user_agent_->setRegistrationRetryTime(SIP_RETRY_TIME);

		// Always force registration, else the UserAgent thinks the device is already registered & does not
		// try to register device.
		user_agent_->registerUserAgent(true);
    }

    void 
    sipclient_signaling::start_useragent(void)
    {
		if (user_agent_ && !user_agent_->is_running())
			user_agent_->start();
    }

    void 
    sipclient_signaling::stop_useragent(void)
    {
		if (user_agent_ && user_agent_->is_running())
			user_agent_->stop();
    }

    void 
    sipclient_signaling::restart_useragent(int port, bool disable_udp,
					   const std::string& passwd)
    {
		// destroyed by reset
		user_agent_.reset();

		user_agent_ = std::shared_ptr<UserAgent>(new UserAgent(port, passwd.c_str(), NULL, disable_udp));

		// init
		init();

		// set the profile
		user_agent_->setProfileAor(profile_aor_);

		// start the UA
		start_useragent();

		// register the user agent
		register_useragent();
    }

    void 
    sipclient_signaling::execute_offer_useragent(const std::string& call_id, bool accept_call /*= true*/,
						 int status_code /*= 200*/)
    {
		if (user_agent_)
			user_agent_->offerUserAgent(call_id, accept_call, status_code);
    }

    void 
    sipclient_signaling::execute_bye_useragent(const std::string& call_id)
    {
		if (user_agent_)
			user_agent_->byeUserAgent(call_id);
    }

    void 
    sipclient_signaling::execute_invite_useragent(const std::string& remote_uri)
    {
		resip::SdpContents sdp = local_sdp_.toSdpContents();
		if (user_agent_)
			user_agent_->inviteRequest(remote_uri, &sdp);
    }

void
sipclient_signaling::setup_local_SDP(void)
{
    std::string connection_str = "c=IN IP4 " + local_address_ + "\r\n";

    // Basic sip call SDP info.
    std::string dataStr = "v=0\r\n";
    dataStr += "o=Pandalume 0 0 IN IP4 " + local_address_ + "\r\n";
    dataStr += "s=Pandalume\r\n";
    dataStr += connection_str;
    dataStr += "t=0 0\r\n";

	// Change if audio stream is active or inactive.
	std::string audioStr = "m=audio 39423 RTP/AVP 96 9 0 8 98 99 101 102\r\n";
	audioStr += "a=rtpmap:96 opus/48000/2\r\n";
	audioStr += "a=rtpmap:97 SILK/16000\r\n";
	audioStr += "a=rtpmap:98 speex/16000\r\n";
	audioStr += "a=rtpmap:99 speex/8000\r\n";
	audioStr += "a=rtpmap:101 telephone-event/8000\r\n";
	audioStr += "a=rtpmap:102 telephone-event/16000\r\n";
	audioStr += "a=fmtp:96 useinbandfec=1; stereo=0; sprop-stereo=0\r\n";
	audioStr += "a=fmtp:98 vbr=on\r\n";
	audioStr += "a=fmtp:99 vbr=on\r\n";
	audioStr += "a=fmtp:101 0-16\r\n";
	audioStr += "a=fmtp:102 0-16\r\n";
	audioStr += "a=sendrecv\r\n";

    std::string videoStr = "m=video 37818 RTP/AVP 96 97 98\r\n";
	videoStr += "a=rtpmap:96 H264/90000\r\n";
    videoStr += "a=rtpmap:97 VP8/90000\r\n";
    //videoStr += "a=rtpmap:98 MP4V-ES/90000\r\n";
   // videoStr += "a=rtpmap:101 telephone-event/90000\r\n";
    //videoStr += "a=fmtp:96 packetization-mode=1;profile-level-id=42801F\r\n";
    //videoStr += "a=fmtp:98 profile-level-id=3\r\n";
	videoStr += "a=fmtp:98 profile-level-id=428016;packetization-mode=0\r\n";
	//videoStr += "a=fmtp:101 0-16\r\n";
    videoStr += "a=sendrecv\r\n";

    std::string tmpDataStr = dataStr + audioStr; //+ videoStr;

	Data* txt = new Data(tmpDataStr);
    const HeaderFieldValue hfv(txt->data(), (unsigned int) txt->size());
    const Mime type("application", "sdp");
    SdpContents sdp_contents(hfv, type);

    local_sdp_ = SessionSdp(&sdp_contents);

    delete txt;
}
// /*
// v=0
// o=000FFF0B005B 1909 3484 IN IP4 10.0.0.9
// s=LPA_Communicator_Call
// c=IN IP4 10.0.0.9
// t=0 0
// m=audio 39423 RTP/AVP 96 9 0 8 97 98 99 101 100 102
// a=rtpmap:96 opus/48000/2
// a=rtpmap:97 SILK/16000
// a=rtpmap:98 speex/16000
// a=rtpmap:99 speex/8000
// a=rtpmap:101 telephone-event/48000
// a=rtpmap:100 telephone-event/8000
// a=rtpmap:102 telephone-event/16000
// a=fmtp:96 useinbandfec=1; stereo=0; sprop-stereo=0
// a=fmtp:98 vbr=on
// a=fmtp:99 vbr=on
// a=sendrecv
// m=video 37818 RTP/AVP 96 97 98 101
// a=rtpmap:96 H264/90000
// a=rtpmap:97 VP8/90000
// a=rtpmap:98 MP4V-ES/90000
// a=rtpmap:101 telephone-event/90000
// a=fmtp:96 packetization-mode=1;profile-level-id=42801F
// a=fmtp:98 profile-level-id=3
// a=sendrecv
// */

}
