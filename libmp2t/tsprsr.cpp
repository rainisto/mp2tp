#include "stdafx.h"
#include "tsprsr.h"

#include "tspckt.h"

namespace lcss
{
	class TSParser::TSParserImpl
	{
	public:
		TSParserImpl() {};

	public:
		TransportPacket _tspckt;
		UINT16	_cursor{};
		UINT64	_count{};
		UINT32	_packetSize{ lcss::TransportPacket::TS_SIZE };
	};
}

/////////////////////////////////////////////////////////////////////////////
// TSParser

lcss::TSParser::TSParser()
	:_pimpl(std::make_unique<lcss::TSParser::TSParserImpl>())
{

}

lcss::TSParser::~TSParser()
{

}

void lcss::TSParser::parse(const BYTE* stream, UINT32 len)
{
	UINT32 i = 0;
	while (i < len)
	{
		// Malformed stream. Not on the 188 boundary. Find the sync byte.
		if (*(stream + i) != 0x47)
		{
			// Converting AVCHD packets to TS packets
			if (_pimpl->_packetSize != lcss::TransportPacket::TS_SIZE)
			{
				i += _pimpl->_packetSize - lcss::TransportPacket::TS_SIZE;
			}
			else
			{
				i++;
			}
		}
		// The TS packet is contain in the stream buffer
		else if (i + lcss::TransportPacket::TS_SIZE <= len)
		{
			if (_pimpl->_tspckt.length() == 0)
			{
				_pimpl->_tspckt.parse(stream + i);
				i += lcss::TransportPacket::TS_SIZE;
				onPacket(_pimpl->_tspckt);
				_pimpl->_tspckt = lcss::TransportPacket();
				_pimpl->_count++;
			}
		}
		// The TS packet spans across two stream buffers
		else if (i + lcss::TransportPacket::TS_SIZE > len)
		{
			i++;
		}
	}
}

void lcss::TSParser::onPacket(lcss::TransportPacket& pckt)
{

}

UINT64 lcss::TSParser::packetCount() const
{
	return _pimpl->_count;
}

void lcss::TSParser::setPacketSize(UINT32 sz)
{
	_pimpl->_packetSize = sz;
}