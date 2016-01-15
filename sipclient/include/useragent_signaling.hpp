
#ifndef USERAGENT_SIGNALING_HPP_
#define USERAGENT_SIGNALING_HPP_

#include <boost/shared_ptr.hpp>
#include "UserAgent.hpp"

//using namespace resip
using namespace SipUserAgent;

namespace sipclient_console_app
{

    static const uint32_t SIP_REG_TIME = 600;  //10 minutes
    static const uint32_t SIP_RETRY_TIME = 10; //10 seconds

    class useragent_signaling : public IRegistrationCallback,
    				public IInviteCallback,
				public ISessionCallback
    {
    public:

	useragent_signaling(const std::string& local_address);
	virtual ~useragent_signaling();

	//This is how we get registration results
	virtual void OnResult(RegResult reg_result, 
			      const std::string& reg_response, 
			      const std::string& method_string, 
			      int status_code, 
			      const std::string& call_id);

	//This is how we get invite results
	virtual void OnResult(InviteResult inviteResult, 
			      const std::string& invite_response, 
			      const std::string& method_string, 
			      int status_code, 
			      const std::string& call_id);

	// this is how we get session change notifications
	virtual void OnSessionChanged(SessionStatus ss, 
				      SessionDialog* dialog);
	// always init first
	void init(void);
	// then set the profile
	static std::string set_profile_aor(const std::string& display_name, const std::string& user_name, const std::string& proxy_ip);
	// register
	void register_useragent(void);
	// start the user agent
	void start_useragent(void);
	// stop the useragent
	void stop_useragent(void);
	// restart the useragent
	void restart_useragent(int port, bool bDisableUDP,
			       const std::string& profile_aor,
			       const std::string& passwd);
	
	// answer/reject call
	void execute_offer_useragent(const std::string& call_id,
				     bool accept_call = true,
				     int status_code = 200);
	// hangup the call
	void execute_bye_useragent(const std::string& call_id);
	// send an invite to an AOR
	void execute_invite_useragent(const std::string& remote_uri);

	std::string get_call_id(void) const { return call_id_; }

    private:

	void setup_local_SDP(void);
	bool is_forking(void);

    private:

	resip::SharedPtr<RegistrationHandler> reg_handler_;
	resip::SharedPtr<InviteHandler> invite_handler_;
	boost::shared_ptr<UserAgent> user_agent_;
	std::string local_address_;
	std::string call_id_;
	SessionSdp local_sdp_;
    };

}

#endif
