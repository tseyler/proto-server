
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* SessionSdp.hpp                                                            *
* Author: Terry Seyler							                            *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#ifndef SESSIONSDP_HPP_
#define SESSIONSDP_HPP_

#include <string>
#include <vector>
#include <map>
#include "sip/resip_stack.h"

namespace SipUserAgent
{

	typedef std::vector<int>					SdpFormatCollection;
	typedef	SdpFormatCollection::iterator		SdpFormatIterator;

	typedef std::map<int, std::string>			SdpRtpMap;
	typedef SdpRtpMap::iterator					SdpRtpMapIterator;

	typedef std::vector<std::string>			SdpAttributeCollection;
	typedef SdpAttributeCollection::iterator	SdpAttributeIterator;

	class SessionSdp; // forward
	typedef std::shared_ptr<SessionSdp>			SessionSdpPtr;

	class SessionSdp
	{
	public:

		class SdpConnection;
		class SdpMedia;
		class SdpOrigin;
		class SdpTime;

		typedef std::vector<SdpMedia*>				SdpMediaCollection;
		typedef SdpMediaCollection::iterator		SdpMediaIterator;

		typedef std::vector<SdpTime*>				SdpTimeCollection;
		typedef SdpTimeCollection::iterator			SdpTimeIterator;

		typedef std::list<SdpConnection>			SdpConnectionCollection;
		typedef SdpConnectionCollection::iterator	SdpConnectionIterator;

		SessionSdp() : 	sdpVersion_(0),
						sessionName_("")
		{ }
		SessionSdp(const std::string& sessionName, int version = 0) : 	sdpVersion_(version),
																		sessionName_(sessionName)
		{ }
		SessionSdp(resip::SdpContents* sdp);
		SessionSdp(const SessionSdp& session);
		virtual ~SessionSdp();

		SessionSdp&						operator=(const SessionSdp& session);
		void							copy(const SessionSdp& session);

		std::string						toString(void);
		resip::SdpContents				toSdpContents(void);

		// getters
		int 							getSdpVersion(void) const { return sdpVersion_; }
		std::string 					getSessionName(void) const { return sessionName_; }
		SdpConnection					getConnection(void) const	{ return sessionConnection_; }
		SdpOrigin						getOrigin(void) const { return sessionOrigin_; }
		SdpMedia* 						getFrontMedia(void);
		SdpMedia* 						getNextMedia(SdpMedia* sdpMedia);
		SdpTime*						getFrontTime(void);
		SdpTime*						getNextTime(SdpTime* sdpTime);

        SdpMediaCollection&             getSdpMediaCollection(void) { return sdpMediaCollection_; }

        // setters
		void 							setSdpVersion(int version) { sdpVersion_ = version; }
		void 							setSdpSessionName(const std::string& name) { sessionName_ = name; }

        void							negotiateMedia(SessionSdpPtr remote_sdp);

		class SdpConnection
		{
		public:

			SdpConnection();
			SdpConnection(const std::string& address, unsigned long ttl = 0UL);
			SdpConnection(const SdpConnection& connection);

			SdpConnection&				operator=(const SdpConnection& connection);
			void						copy(const SdpConnection& connection);

			std::string					toString(void);
			resip::SdpContents::Session::Connection	toSdpContents(void);

			// getters
			std::string 				getAddress(void) const { return address_; }
			unsigned long				getTtl(void) const { return ttl_; }

			// setters
			void						setAddress(const std::string& address) { address_ = address; }
			void						setTtl(unsigned long ttl) { ttl_ = ttl; }

		private:

			std::string 				address_;
			unsigned long				ttl_;
		};

		class SdpMedia
		{
		public:

			enum MediaType { 			mediaNotSpecified,
										mediaAudio,
										mediaVideo,
			};

			enum SendRecv { 			srNotSpecified,
										srInactive,
										srSendRecv,
										srSend,
										srRecv,
			};

			static SendRecv 			mediumToSendRecv(resip::SdpContents::Session::Medium& media);
			static std::string 			sendRecvToString(SendRecv sr);

			SdpMedia();
			SdpMedia(const std::string& name, int port, int multicast, const std::string& protocol);
			SdpMedia(const SdpMedia& media);

			SdpMedia&					operator=(const SdpMedia& media);
			void						copy(const SdpMedia& media);

			std::string					toString(void);
			std::string					rtpMapToString(void);
			std::string					attributesToString(void);
			resip::SdpContents::Session::Medium	toSdpContents(void);

			// getters
			std::string 				getName(void) const { return name_; }
			int							getPort(void) const { return port_; }
			int							getMulticast(void) const { return multicast_; }
			std::string 				getProtocol(void) const { return protocol_; }
			SdpFormatCollection			getFormats(void) const { return formats_; }
			SdpRtpMap					getRtpMap(void) const { return rtpmaps_; }
			MediaType					getMediaType(void) const;
			SdpAttributeCollection		getAttributes(void) const { return attributes_; }
			SendRecv					getSendRecv(void);
			SdpConnection*				getFrontConnection(void);

			/**	This function gets the connections list from the media.
			 *	@return list<resip::SdpContents::Session::Connection> from the media. */
			SdpConnectionCollection		getConnections(void) const { return connections_ ; }

			// setters
			void						setName(const std::string& name) { name_ = name; }
			void						setPort(int port) { port_ = port; }
			void						setMulticast(int multicast) { multicast_ = multicast; }
			void						setProtocol(const std::string& protocol) { protocol_ = protocol; }

			// media format routines
			void 						addFormatContainer(resip::SdpContents::Session::Medium& media);
			void 						addFormat(int format);
			void 						removeFormat(int format);
			void 						addRtpMapContainer(resip::SdpContents::Session::Medium& media);
			void 						addRtpMap(int codec, const std::string& value);

			/** Adds media connections to SdpMedia	from the media connections list.
			 *	@param media
			 *		The session media from which to add the connections list. */
			void 						addMediaConnections(resip::SdpContents::Session::Medium& media);

			void 						removeRtpMap(int codec);

			// attribute routines
			void						addSendRecvAttribute(resip::SdpContents::Session::Medium& media);
			void						addSendRecvAttribute(SendRecv sr);
			void						clearSendRecvAttribute(void);
			bool						sendRecvAttributeExists(SendRecv sr);

			void						addImageAttributes(resip::SdpContents::Session::Medium& media);
			void						addFmtpAttributes(resip::SdpContents::Session::Medium& media);

			// media negotiation routines
			SdpFormatCollection			negotiateFormats(SdpFormatCollection& formats);
			SdpFormatCollection			negotiateFormats(SdpMedia& sdpMedia);
			int							primaryFormat(void);
			void						andFormats(SdpFormatCollection& formats);
			void						andFormats(SdpMedia& sdpMedia);
			bool						selectFormat(int format);
			bool						selectFormat(void);	// uses the primary format
			bool						oneFormat(void) const { return (formats_.size() == 1); }
			bool						sameFormats(SdpMedia& sdpMedia);

		private:

			std::string					name_;
			int							port_;
			int							multicast_;
			std::string					protocol_;
			SendRecv					sendRecv_;
			SdpFormatCollection			formats_;
			SdpRtpMap					rtpmaps_;
			SdpAttributeCollection		attributes_;

			// Stores the media connections list for this particular media.
			SdpConnectionCollection 	connections_;
		};

		class SdpOrigin
		{
		public:

			SdpOrigin();
			SdpOrigin(const std::string& user, UInt64 sessionId, UInt64 version, const std::string& address);
			SdpOrigin(const SdpOrigin& origin);

			SdpOrigin&					operator=(const SdpOrigin& origin);
			void						copy(const SdpOrigin& origin);

			std::string					toString(void);
			resip::SdpContents::Session::Origin	toSdpContents(void);

			// getters
			std::string					getUser(void) const	{ return user_; }
			UInt64						getSessionId(void) const	{ return sessionId_; }
			UInt64						getVersion(void) const { return version_; }
			std::string					getAddress(void) const { return address_; }

			// setters
			void						setUser(const std::string& user) { user_ = user; }
			void						setSessionId(UInt64 sessionId) { sessionId_ = sessionId; }
			void						setVersion(UInt64 version) { version_ = version; }
			void						setAddress(const std::string& address) { address_ = address; }

		private:

			std::string					user_;
			UInt64						sessionId_;
			UInt64						version_;
			std::string					address_;
		};

		class SdpTime
		{
		public:

			SdpTime() : start_(0UL), stop_(0UL)
			{ }
			SdpTime(UInt64 start, UInt64 stop) : start_(start), stop_(stop)
			{ }
			SdpTime(const SdpTime& time);

			SdpTime& 					operator=(const SdpTime& time);
			void						copy(const SdpTime& time);

			std::string					toString(void);
			resip::SdpContents::Session::Time	toSdpContents(void);

			// getters
			UInt64						getStartTime(void) const { return start_; }
			UInt64						getStopTime(void) const { return stop_; }

			// setters
			void						setStartTime(UInt64 start) { start_ = start; }
			void						setStopTime(UInt64 stop) { stop_ = stop; }


		private:

			UInt64						start_;
			UInt64						stop_;
		};

	protected:

		int								sdpVersion_;
		std::string						sessionName_;
		SdpConnection					sessionConnection_;
		SdpOrigin						sessionOrigin_;
		SdpMediaCollection				sdpMediaCollection_;
		SdpTimeCollection				sdpTimeCollection_;
	};


}


#endif /* SESSIONSDP_HPP_ */
