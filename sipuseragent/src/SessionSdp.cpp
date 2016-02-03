
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* SessionSdp.cpp                                                            *
* Author: Terry Seyler							    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#include <sstream>
#include <list>

#include "userAgentHelper.h"
#include "SessionSdp.hpp"

using namespace resip;

SipUserAgent::SessionSdp::SessionSdp(SdpContents* sdp) :	sdpVersion_(-1),
														sessionName_(""),
				sessionConnection_(SipUserAgent::makeString(sdp->session().connection().getAddress()), 
									sdp->session().connection().ttl()),
				sessionOrigin_(SipUserAgent::makeString(sdp->session().origin().user()),
								sdp->session().origin().getSessionId(),
								sdp->session().origin().getVersion(),
								SipUserAgent::makeString(sdp->session().origin().getAddress()))
{
	assert(sdp);

	SdpContents::Session session = sdp->session();
	sdpVersion_ = session.version();
	sessionName_ = SipUserAgent::makeString(session.name());

	// SdpMedia
	SdpContents::Session::MediumContainer mediaContainer = session.media();
	SdpContents::Session::MediumContainer::iterator mit = mediaContainer.begin();
	while (mit != mediaContainer.end())
	{
		SdpContents::Session::Medium media = *mit;
		std::string mediaName = SipUserAgent::makeString(media.name());
		int mediaPort = static_cast<int>(media.port());
		int mediaMulticast = static_cast<int>(media.multicast());
		std::string mediaProtocol = SipUserAgent::makeString(media.protocol());
		SdpMedia* sdpMedia = new SdpMedia(mediaName, mediaPort, mediaMulticast, mediaProtocol);

		assert(sdpMedia);
		sdpMedia->addFormatContainer(media);
		sdpMedia->addRtpMapContainer(media);
		sdpMedia->addFmtpAttributes(media);
		sdpMedia->addImageAttributes(media);
		sdpMedia->addSendRecvAttribute(media);

		// Add Media Connections list to the media class.
		sdpMedia->addMediaConnections(media);

		SipUserAgent::addToCollection<SdpMediaCollection, SdpMedia*>(sdpMediaCollection_, sdpMedia);
		mit++;
	}

	// SdpTime
	std::list<SdpContents::Session::Time>& times = session.getTimes();
	std::list<SdpContents::Session::Time>::iterator tit = times.begin();
	while (tit != times.end())
	{
		SdpContents::Session::Time time = *tit;
		SdpTime* sdpTime = new SdpTime(time.getStart(), time.getStop());
		SipUserAgent::addToCollection<SdpTimeCollection, SdpTime*>(sdpTimeCollection_, sdpTime);
		tit++;
	}
}

SipUserAgent::SessionSdp::SessionSdp(const SessionSdp& session)
{
	copy(session);
}

SipUserAgent::SessionSdp::~SessionSdp()
{
	//must free pointers before emptying collection
	for(SdpMediaIterator iter=sdpMediaCollection_.begin(); iter != sdpMediaCollection_.end(); ++iter)
		delete *iter;
	emptyCollection<SdpMediaCollection>(sdpMediaCollection_);
	for(SdpTimeIterator iter=sdpTimeCollection_.begin(); iter != sdpTimeCollection_.end(); ++iter)
		delete *iter;
	emptyCollection<SdpTimeCollection>(sdpTimeCollection_);
}

SipUserAgent::SessionSdp&
SipUserAgent::SessionSdp::operator=(const SessionSdp& session)
{
	if (this == &session)
		return *this;

	copy(session);

	return *this;
}

void
SipUserAgent::SessionSdp::copy(const SessionSdp& session)
{
	sdpVersion_ = session.getSdpVersion();
	sessionName_ = session.getSessionName();
	sessionConnection_ = session.getConnection();
	sessionOrigin_ = session.getOrigin();

	// empty the collection before the copy
	// must free pointers before empty
	for(SdpMediaIterator iter=sdpMediaCollection_.begin(); iter != sdpMediaCollection_.end(); ++iter)
		delete *iter;
	SipUserAgent::emptyCollection<SdpMediaCollection>(sdpMediaCollection_);

	SdpMedia* media = (const_cast<SessionSdp&>(session)).getFrontMedia();
	while (media)
	{
		SipUserAgent::addToCollection<SdpMediaCollection, SdpMedia*>(sdpMediaCollection_, new SdpMedia(*media));
		media = (const_cast<SessionSdp&>(session)).getNextMedia(media);
	}
}

std::string
SipUserAgent::SessionSdp::toString(void)
{
	std::stringstream ss;
	ss << "v=" << sdpVersion_ << CRLF;
	ss << sessionOrigin_.toString();
	ss << "s=" << sessionName_ << CRLF;
	ss << sessionConnection_.toString();

	SdpTime* sdpTime = getFrontTime();
	if (sdpTime)
		ss << sdpTime->toString();

	SdpMedia* sdpMedia = getFrontMedia();
	while (sdpMedia)
	{
		ss << sdpMedia->toString();
		SdpConnection* connection = sdpMedia->getFrontConnection();
		if (connection)
			ss << connection->toString();
		ss << sdpMedia->rtpMapToString();
		ss << sdpMedia->attributesToString();
		sdpMedia = getNextMedia(sdpMedia);
	}

	return ss.str();
}

SdpContents
SipUserAgent::SessionSdp::toSdpContents(void)
{
	SdpContents sdp;
	SdpContents::Session::Origin origin = sessionOrigin_.toSdpContents();
	SdpContents::Session session = SdpContents::Session(sdpVersion_, origin, sessionName_.c_str());
	session.connection() = sessionConnection_.toSdpContents();

	SdpTime* sdpTime = getFrontTime();
	if (sdpTime)
		session.addTime(sdpTime->toSdpContents());

	SdpMedia* sdpMedia = getFrontMedia();
	while (sdpMedia)
	{
		session.addMedium(sdpMedia->toSdpContents());
		sdpMedia = getNextMedia(sdpMedia);
	}

	sdp.session() = session;

	return sdp;
}

SipUserAgent::SessionSdp::SdpMedia*
SipUserAgent::SessionSdp::getFrontMedia(void)
{
	return SipUserAgent::getFrontFromCollection<SdpMediaCollection, SdpMedia*>(sdpMediaCollection_, NULL);
}

SipUserAgent::SessionSdp::SdpMedia*
SipUserAgent::SessionSdp::getNextMedia(SdpMedia* sdpMedia)
{
	SdpMedia* nextSdpMedia = SipUserAgent::getNextFromCollection<SdpMediaCollection,
								SdpMediaIterator, SdpMedia*>(sdpMediaCollection_, sdpMedia);

	return (nextSdpMedia != sdpMedia) ? nextSdpMedia : NULL;
}

SipUserAgent::SessionSdp::SdpTime*
SipUserAgent::SessionSdp::getFrontTime(void)
{
	return SipUserAgent::getFrontFromCollection<SdpTimeCollection, SdpTime*>(sdpTimeCollection_, NULL);
}

SipUserAgent::SessionSdp::SdpTime*
SipUserAgent::SessionSdp::getNextTime(SdpTime* sdpTime)
{
	SdpTime* nextSdpTime = SipUserAgent::getNextFromCollection<SdpTimeCollection,
								SdpTimeIterator, SdpTime*>(sdpTimeCollection_, sdpTime);

	return (nextSdpTime != sdpTime) ? nextSdpTime : NULL;
}

void
SipUserAgent::SessionSdp::negotiateMedia(SessionSdpPtr remote_sdp)
{
	SessionSdp::SdpMedia* remoteSdpMedia = remote_sdp->getFrontMedia();
	while (remoteSdpMedia)
	{
		SessionSdp::SdpMedia* sessionSdpMedia = getFrontMedia();
		while (sessionSdpMedia)
		{
			if (remoteSdpMedia->getMediaType() == sessionSdpMedia->getMediaType())
			{
				sessionSdpMedia->andFormats(*remoteSdpMedia);
				// negotiate sendrecv
				switch (sessionSdpMedia->getSendRecv())
				{
					case SessionSdp::SdpMedia::srSendRecv:

						if (remoteSdpMedia->sendRecvAttributeExists(SessionSdp::SdpMedia::srSend))	// remote went to a hold
							sessionSdpMedia->addSendRecvAttribute(SessionSdp::SdpMedia::srRecv);
						break;
					case SessionSdp::SdpMedia::srRecv:

						if (remoteSdpMedia->sendRecvAttributeExists(SessionSdp::SdpMedia::srSendRecv))	// remote went off hold
							sessionSdpMedia->addSendRecvAttribute(SessionSdp::SdpMedia::srSendRecv);
						break;
					case SessionSdp::SdpMedia::srNotSpecified:
					case SessionSdp::SdpMedia::srInactive:
					case SessionSdp::SdpMedia::srSend:

						break;
				}
			}
			sessionSdpMedia = getNextMedia(sessionSdpMedia);
		}
		remoteSdpMedia = remote_sdp->getNextMedia(remoteSdpMedia);
	}
}

//////////////////////////////// SdpConnection /////////////////////////////////////

SipUserAgent::SessionSdp::SdpConnection::SdpConnection() : address_(""), ttl_(0)
{ }

SipUserAgent::SessionSdp::SdpConnection::SdpConnection(const std::string& address, 
													  unsigned long ttl /*= 0UL*/) :	address_(address),
																						ttl_(ttl)
{ }

SipUserAgent::SessionSdp::SdpConnection::SdpConnection(const SdpConnection& connection)
{
	copy(connection);
}

SipUserAgent::SessionSdp::SdpConnection&
SipUserAgent::SessionSdp::SdpConnection::operator=(const SdpConnection& connection)
{
	if (this == &connection)
		return *this;

	copy(connection);

	return *this;
}

void
SipUserAgent::SessionSdp::SdpConnection::copy(const SdpConnection& connection)
{
	address_ = connection.getAddress();
	ttl_ = connection.getTtl();
}

std::string
SipUserAgent::SessionSdp::SdpConnection::toString(void)
{
	std::stringstream ss;

	if (!address_.empty())
		ss << "c=" << IP4 << SPACE << address_;
	if (ttl_)
		ss << "/" << ttl_;
	ss << CRLF;

	return ss.str();
}
SdpContents::Session::Connection
SipUserAgent::SessionSdp::SdpConnection::toSdpContents(void)
{
	return SdpContents::Session::Connection(SdpContents::IP4, address_.c_str(), ttl_);
}

//////////////////////////////// SdpMedia //////////////////////////////////////////

SipUserAgent::SessionSdp::SdpMedia::SdpMedia() : 	name_("none"),
													port_(0),
													multicast_(0),
													protocol_("none"),
													sendRecv_(srNotSpecified)
{ }

SipUserAgent::SessionSdp::SdpMedia::SdpMedia(const std::string& name,
											int port, int multicast,
											const std::string& protocol) : 	name_(name),
																			port_(port),
																			multicast_(multicast),
																			protocol_(protocol),
																			sendRecv_(srNotSpecified)
{ }

SipUserAgent::SessionSdp::SdpMedia::SdpMedia(const SdpMedia& media)
{
	copy(media);
}

SipUserAgent::SessionSdp::SdpMedia&
SipUserAgent::SessionSdp::SdpMedia::operator=(const SdpMedia& media)
{
	if (this == &media)
		return *this;

	copy(media);

	return *this;
}

void
SipUserAgent::SessionSdp::SdpMedia::copy(const SdpMedia& media)
{
	name_ = media.getName();
	port_ = media.getPort();
	multicast_ = media.getMulticast();
	protocol_ = media.getProtocol();
	formats_ = media.getFormats();
	rtpmaps_ = media.getRtpMap();
	attributes_ = media.getAttributes();
}

std::string
SipUserAgent::SessionSdp::SdpMedia::toString(void)
{
	std::stringstream ss;

	if (name_ != "none")
	{
		ss << "m=" << name_ << SPACE << port_ << SPACE << protocol_;
		SdpFormatIterator fit = formats_.begin();
		while (fit != formats_.end())
			ss << SPACE << *fit++;
		ss << CRLF;
	}

	return ss.str();
}

std::string
SipUserAgent::SessionSdp::SdpMedia::rtpMapToString(void)
{
	std::stringstream ss;

	if (rtpmaps_.size())
	{
		SdpFormatIterator fit = formats_.begin();
		while (fit != formats_.end())
		{
			SdpRtpMapIterator rit = rtpmaps_.find(*fit);
			if (rit != rtpmaps_.end())
			{
				std::string value = (*rit).second;
				ss << "a=rtpmap:" << value << CRLF;
			}
			fit++;
		}
	}

	return ss.str();
}

std::string
SipUserAgent::SessionSdp::SdpMedia::attributesToString(void)
{
	std::stringstream ss;

	if (attributes_.size())
	{
		SdpAttributeIterator ait = attributes_.begin();
		while (ait != attributes_.end())
		{
			ss << "a=" << *ait << CRLF;
			ait++;
		}
	}

	return ss.str();
}

SdpContents::Session::Medium
SipUserAgent::SessionSdp::SdpMedia::toSdpContents(void)
{
	SdpContents::Session::Medium medium = SdpContents::Session::Medium(name_.c_str(), port_, multicast_, protocol_.c_str());
	// add the formats
	SdpFormatIterator fit = formats_.begin();
	while (fit != formats_.end())
	{
		int format = *fit;
		medium.addFormat(Data(format));
		fit++;
	}
	// add rtpmap attributes
	fit = formats_.begin();
	while (fit != formats_.end())
	{
		SdpRtpMapIterator rit = rtpmaps_.find(*fit);
		if (rit != rtpmaps_.end())
		{
			std::string value = (*rit).second;
			medium.addAttribute("rtpmap", value.c_str());
		}
		fit++;
	}

	// add attributes
	SdpAttributeIterator ait = attributes_.begin();
	while (ait != attributes_.end())
	{
		std::string attribute = *ait;
		medium.addAttribute(attribute.c_str());
		ait++;
	}

	// add connections
	SdpConnectionIterator cit = connections_.begin();
	while (cit != connections_.end())
	{
		SdpConnection connection = *cit;
		medium.addConnection(connection.toSdpContents());
		cit++;
	}

	return medium;
}

SipUserAgent::SessionSdp::SdpMedia::MediaType
SipUserAgent::SessionSdp::SdpMedia::getMediaType(void) const
{
	MediaType type(mediaNotSpecified);

	if (name_ == "audio")
		type = mediaAudio;
	if (name_ == "video")
		type = mediaVideo;

	return type;
}

SipUserAgent::SessionSdp::SdpMedia::SendRecv
SipUserAgent::SessionSdp::SdpMedia::getSendRecv(void)
{
	if (sendRecvAttributeExists(srInactive))
		return srInactive;
	if (sendRecvAttributeExists(srSendRecv))
		return srSendRecv;
	if (sendRecvAttributeExists(srSend))
		return srSend;
	if (sendRecvAttributeExists(srRecv))
		return srRecv;

	return srNotSpecified;
}

SipUserAgent::SessionSdp::SdpConnection*
SipUserAgent::SessionSdp::SdpMedia::getFrontConnection(void)
{
	return connections_.size() ? &connections_.front() : NULL;
}

void
SipUserAgent::SessionSdp::SdpMedia::addFormat(int format)
{
	addToCollection<SdpFormatCollection, int>(formats_, format);
}

void
SipUserAgent::SessionSdp::SdpMedia::removeFormat(int format)
{
	removeFromCollection<SdpFormatCollection, SdpFormatIterator, int>(formats_, format);
}

void
SipUserAgent::SessionSdp::SdpMedia::addFormatContainer(SdpContents::Session::Medium& media)
{
	std::list<Data> dataContainer = media.getFormats();
	std::list<Data>::iterator dit = dataContainer.begin();
	while (dit != dataContainer.end())
	{
		Data data = *dit;
		int format = data.convertInt();
		addFormat(format);
		dit++;
	}
}

void
SipUserAgent::SessionSdp::SdpMedia::addRtpMapContainer(SdpContents::Session::Medium& media)
{
	if (media.exists("rtpmap"))
	{
		std::list<Data> dataContainer = media.getValues("rtpmap");
		std::list<Data>::iterator dit = dataContainer.begin();
		while (dit != dataContainer.end())
		{
			Data data = *dit;
			std::string value = SipUserAgent::makeString(data);
			int codec = SipUserAgent::parseRtpMapAttribute(value);
			if (codec >= 0)
				addRtpMap(codec, value);
			dit++;
		}
	}
}

void
SipUserAgent::SessionSdp::SdpMedia::addRtpMap(int codec, const std::string& value)
{
	rtpmaps_[codec] = value;
}

void
SipUserAgent::SessionSdp::SdpMedia::addMediaConnections(SdpContents::Session::Medium& media)
{
	// Get the connections iterator.
	std::list<resip::SdpContents::Session::Connection>::const_iterator connIter;

	if (media.getConnections().empty())
		return;

	resip::SdpContents::Session::Connection conn = media.getConnections().front();
	Data data = conn.getAddress();
	unsigned long ttl = conn.ttl();
	std::string value = SipUserAgent::makeString(data);

	if (strcmp(value.c_str(), "") != 0)
	{
		SdpConnection sdpConn(value, ttl);
		connections_.push_back(sdpConn);
	}
}

void
SipUserAgent::SessionSdp::SdpMedia::removeRtpMap(int codec)
{
	rtpmaps_.erase(codec);
}

SipUserAgent::SessionSdp::SdpMedia::SendRecv
SipUserAgent::SessionSdp::SdpMedia::mediumToSendRecv(SdpContents::Session::Medium& media)
{
	if (media.exists("inactive"))
		return srInactive;
	if (media.exists("sendrecv"))
		return srSendRecv;
	if (media.exists("sendonly"))
		return srSend;
	if (media.exists("recvonly"))
		return srRecv;

	// RS, If not specified, according to IETF @"http://www.ietf.org/rfc/rfc3264.txt" [page 5], default,
	//	if no attribute is specified, it is sendrecv.
	// return srNotSpecified;
	return srSendRecv;
}

std::string
SipUserAgent::SessionSdp::SdpMedia::sendRecvToString(SendRecv sr)
{
	std::string srStr("");

	switch (sr)
	{
		case srInactive:

			srStr = "inactive";
			break;
		case srSendRecv:

			srStr = "sendrecv";
			break;
		case srSend:

			srStr = "sendonly";
			break;
		case srRecv:

			srStr = "recvonly";
			break;
		case srNotSpecified:

			break;
	}

	return srStr;
}

void
SipUserAgent::SessionSdp::SdpMedia::addSendRecvAttribute(SdpContents::Session::Medium& media)
{
	addSendRecvAttribute(mediumToSendRecv(media));
}

void
SipUserAgent::SessionSdp::SdpMedia::addSendRecvAttribute(SendRecv sr)
{
	clearSendRecvAttribute();	//should only be one sendrecv attribute per media

	if (sr != srNotSpecified)
		SipUserAgent::addToCollection<SdpAttributeCollection, std::string>(attributes_, sendRecvToString(sr));
}

void
SipUserAgent::SessionSdp::SdpMedia::clearSendRecvAttribute(void)
{
	removeFromCollection<SdpAttributeCollection, SdpAttributeIterator, std::string>(attributes_, sendRecvToString(srInactive));
	removeFromCollection<SdpAttributeCollection, SdpAttributeIterator,std::string>(attributes_, sendRecvToString(srSendRecv));
	removeFromCollection<SdpAttributeCollection, SdpAttributeIterator, std::string>(attributes_, sendRecvToString(srSend));
	removeFromCollection<SdpAttributeCollection, SdpAttributeIterator, std::string>(attributes_, sendRecvToString(srRecv));
}

bool
SipUserAgent::SessionSdp::SdpMedia::sendRecvAttributeExists(SendRecv sr)
{
	std::string sendRecv("");
	sendRecv = SipUserAgent::getFrontFromCollection<SdpAttributeCollection, std::string>(attributes_, sendRecv);
	while (!sendRecv.empty())
	{
		if (sendRecv == sendRecvToString(sr))
			return true;
		std::string nextAttribute = SipUserAgent::getNextFromCollection<SdpAttributeCollection,
										SdpAttributeIterator, std::string>(attributes_, sendRecv);
		sendRecv = (sendRecv == nextAttribute) ? "" : nextAttribute;
	}

	return false;
}

SipUserAgent::SdpFormatCollection
SipUserAgent::SessionSdp::SdpMedia::negotiateFormats(SdpFormatCollection& formats)
{
	SdpFormatCollection formatCollection;
	SdpFormatIterator	fit = formats.begin();
	while (fit != formats.end())
	{
		int f = *fit++;
		if (SipUserAgent::getIteratorFromCollection<SdpFormatCollection,
									SdpFormatIterator, int>(formats_, f) != formats_.end())
			SipUserAgent::addToCollection<SdpFormatCollection, int>(formatCollection, f);
	}

	return formatCollection;
}

SipUserAgent::SdpFormatCollection
SipUserAgent::SessionSdp::SdpMedia::negotiateFormats(SdpMedia& sdpMedia)
{
	SdpFormatCollection formats = sdpMedia.getFormats();

	return negotiateFormats(formats);
}

int
SipUserAgent::SessionSdp::SdpMedia::primaryFormat(void)
{
	return getFrontFromCollection<SdpFormatCollection, int>(formats_, -1);
}

void
SipUserAgent::SessionSdp::SdpMedia::andFormats(SdpFormatCollection& formats)
{
	SdpFormatCollection negFormats = negotiateFormats(formats);

	emptyCollection<SdpFormatCollection>(formats_);	// empty and then fill with only the negotiated formats
	copyCollection<SdpFormatCollection>(negFormats, formats_);
}

void
SipUserAgent::SessionSdp::SdpMedia::andFormats(SdpMedia& sdpMedia)
{
	SdpFormatCollection negFormats = negotiateFormats(sdpMedia);

	emptyCollection<SdpFormatCollection>(formats_);	// empty and then fill with only the negotiated formats
	copyCollection<SdpFormatCollection>(negFormats, formats_);
}

bool
SipUserAgent::SessionSdp::SdpMedia::selectFormat(int format)
{
	SdpFormatIterator fit = SipUserAgent::getIteratorFromCollection<SdpFormatCollection,
																SdpFormatIterator, int>(formats_, format);
	if (fit != formats_.end())
	{
		emptyCollection<SdpFormatCollection>(formats_);
		SipUserAgent::addToCollection<SdpFormatCollection, int>(formats_, format);
		return true;
	}

	return false;
}

bool
SipUserAgent::SessionSdp::SdpMedia::selectFormat(void)
{
	return selectFormat(primaryFormat());
}

bool
SipUserAgent::SessionSdp::SdpMedia::sameFormats(SdpMedia& sdpMedia)
{
	SdpFormatCollection formats = sdpMedia.getFormats();

	if (formats.size() == formats_.size())	// they need to be the same size to have a chance being same formats
	{
		SdpFormatIterator fit = formats_.begin();
		while (fit != formats_.end())
		{
			SdpFormatIterator it = SipUserAgent::getIteratorFromCollection<SdpFormatCollection,
																		SdpFormatIterator, int>(formats, *fit++);
			if (it == formats.end())
				return false;
		}

		return true;
	}

	return false;
}



void
SipUserAgent::SessionSdp::SdpMedia::addFmtpAttributes(SdpContents::Session::Medium& media)
{
		if (media.exists("fmtp"))
		{
			std::list<Data> dataContainer = media.getValues("fmtp");
			std::list<Data>::iterator dit = dataContainer.begin();
			while (dit != dataContainer.end())
			{
				Data data = *dit;
				std::string value = "fmtp:" + SipUserAgent::makeString(data);

	//			switch(value)
	//			{
	//			case "inactive":
	//
	//
	//
	//			}

				SipUserAgent::addToCollection<SdpAttributeCollection, std::string>(attributes_, value);
				dit++;
			}
		}
}




void
SipUserAgent::SessionSdp::SdpMedia::addImageAttributes(SdpContents::Session::Medium& media)
{

////	std::vector<std::string> parsedStr;
////	boost::split(parsedStr, )
//
//
//	if (media.exists("a"))
//		media.getValues("a")
//
//
//
////	if (media.exists("inactive"))
////			return srInactive;
////		if (media.exists("sendrecv"))
////			return srSendRecv;
////		if (media.exists("sendonly"))
////			return srSend;
////		if (media.exists("recvonly"))
////			return srRecv;
////
////		// RS, If not specified, according to IETF @"http://www.ietf.org/rfc/rfc3264.txt" [page 5], default,
////		//	if no attribute is specified, it is sendrecv.
////		// return srNotSpecified;
////		return srSendRecv;
////
//
//
//	if (sr != srNotSpecified)
//		SipUserAgent::addToCollection<SdpAttributeCollection, std::string>(attributes_, sendRecvToString(sr));


		if (media.exists("imageattr"))
		{
			std::list<Data> dataContainer = media.getValues("imageattr");
			std::list<Data>::iterator dit = dataContainer.begin();
			while (dit != dataContainer.end())
			{
				Data data = *dit;
				std::string value = "imageAttr:" + SipUserAgent::makeString(data);

	//			switch(value)
	//			{
	//			case "inactive":
	//
	//
	//
	//			}

				SipUserAgent::addToCollection<SdpAttributeCollection, std::string>(attributes_, value);
				dit++;
			}
		}
}





/////////////////////////////// SdpOrigin ////////////////////////////////////

SipUserAgent::SessionSdp::SdpOrigin::SdpOrigin() :	user_("-"),
													sessionId_(0UL),
													version_(0UL),
													address_("")
{ }

SipUserAgent::SessionSdp::SdpOrigin::SdpOrigin(const std::string& user, UInt64 sessionId, UInt64 version,
														const std::string& address) :	user_(user),
																						sessionId_(sessionId),
																						version_(version),
																						address_(address)
{ }

SipUserAgent::SessionSdp::SdpOrigin::SdpOrigin(const SdpOrigin& origin)
{
	copy(origin);
}

SipUserAgent::SessionSdp::SdpOrigin&
SipUserAgent::SessionSdp::SdpOrigin::operator=(const SdpOrigin& origin)
{
	if (this == &origin)
		return *this;

	copy(origin);

	return *this;
}

void
SipUserAgent::SessionSdp::SdpOrigin::copy(const SdpOrigin& origin)
{
	user_ = origin.getUser();
	sessionId_ = origin.getSessionId();
	version_ = origin.getVersion();
	address_ = origin.getAddress();
}

std::string
SipUserAgent::SessionSdp::SdpOrigin::toString(void)
{
	std::stringstream ss;

	ss << "o=" << user_ << SPACE << sessionId_ << SPACE << version_ << SPACE << IP4 << SPACE << address_ << CRLF;

	return ss.str();
}

SdpContents::Session::Origin
SipUserAgent::SessionSdp::SdpOrigin::toSdpContents(void)
{
	return SdpContents::Session::Origin(user_.c_str(), sessionId_, version_, SdpContents::IP4, address_.c_str());
}

/////////////////////////////// SdpTime ////////////////////////////////////

SipUserAgent::SessionSdp::SdpTime::SdpTime(const SdpTime& time)
{
	copy(time);
}

SipUserAgent::SessionSdp::SdpTime&
SipUserAgent::SessionSdp::SdpTime::operator=(const SdpTime& time)
{
	if (this == &time)
		return *this;

	copy(time);

	return *this;
}

void
SipUserAgent::SessionSdp::SdpTime::copy(const SdpTime& time)
{
	start_ = time.getStartTime();
	stop_ = time.getStopTime();
}

std::string
SipUserAgent::SessionSdp::SdpTime::toString(void)
{
	std::stringstream ss;

	ss << "t=" << start_ << SPACE << stop_ << CRLF;

	return ss.str();
}

SdpContents::Session::Time
SipUserAgent::SessionSdp::SdpTime::toSdpContents(void)
{
	return SdpContents::Session::Time(start_, stop_);
}
