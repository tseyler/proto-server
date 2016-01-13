
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* RegistrationHandler.hpp                                                   *
* Author: Terry Seyler						       	    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#ifndef REGISTRATIONHANDLER_HPP_
#define REGISTRATIONHANDLER_HPP_

#include <string>
#include <vector>
#include "sip/resip_dum.h"
#include "UserAgentCallbackImpl.hpp"

namespace SipUserAgent
{
    typedef enum
    {
	regInit,
	regSuccess,
	regRemoved,
	regFailure,
	regRetry,
    } RegResult;

    typedef IUserAgentCallback<RegResult> IRegistrationCallback;
    typedef std::vector<IRegistrationCallback*> RegCallbackCollection;
    typedef RegCallbackCollection::iterator RegCallbackIterator;
    typedef UserAgentCallbackImpl<RegCallbackCollection, RegCallbackIterator, IRegistrationCallback, RegResult>
    RegCallbackImpl;

    class RegistrationHandler : public RegCallbackImpl,
				public resip::ClientRegistrationHandler
    {
    public:

	RegistrationHandler() : 	RegCallbackImpl(regInit),
					registered_(false),
					registration_(NULL),
					regRetrySec_(120)
	    { }
	virtual ~RegistrationHandler()
	    { }

	virtual void 	onSuccess(resip::ClientRegistrationHandle h, const resip::SipMessage& response);
	virtual void 	onRemoved(resip::ClientRegistrationHandle h, const resip::SipMessage& response);
	virtual void 	onFailure(resip::ClientRegistrationHandle h, const resip::SipMessage& response);
	virtual int 	onRequestRetry(resip::ClientRegistrationHandle h, int retrySeconds, const resip::SipMessage& response);

	// setters
	void			setRegistrationRetryTime(unsigned int sec) { regRetrySec_ = sec; }
	void			resetRegistration(void);

	// getters
	unsigned int	getRegistrationRetryTime(void) const { return regRetrySec_; }

	bool 			isRegistered(void) const { return registered_; }
	void			unRegister(void);
	void			stopRegistering(void);

    protected:

	bool 			      registered_;
	resip::ClientRegistration*    registration_;
	unsigned int		      regRetrySec_;
    };
}


#endif /* REGISTRATIONHANDLER_HPP_ */
