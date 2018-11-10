#include <cstdint>

#include "EthernetIIHeader.hpp"
#include "misc.hpp"

#include "MacAddress.hpp"

//==============================================================================
EthernetIIHeader::EthernetIIHeader() :
    DataPacket(1), // always aligned on 1 byte (no alignment)
    ethertype(0)
{
    addDataFields();
}

//==============================================================================
EthernetIIHeader::EthernetIIHeader(std::uint16_t ethertype) :
    EthernetIIHeader()
{
    this->ethertype = ethertype;
}

//==============================================================================
EthernetIIHeader::EthernetIIHeader(const MacAddress& destination,
                                   const MacAddress& source,
                                   std::uint16_t     ethertype) :
    EthernetIIHeader()
{
    // cppcheck-suppress useInitializationList
    this->destination = destination;
    // cppcheck-suppress useInitializationList
    this->source      = source;
    this->ethertype   = ethertype;
}

//==============================================================================
EthernetIIHeader::EthernetIIHeader(const unsigned char* buffer) :
    EthernetIIHeader()
{
    readRaw(buffer);
}

//==============================================================================
EthernetIIHeader::EthernetIIHeader(const unsigned char* buffer,
                                   misc::ByteOrder      byte_order) :
    EthernetIIHeader()
{
    // Ethernet II frames store big endian data by definition
    readRaw(buffer, misc::BIG_ENDIAN);
}

//==============================================================================
EthernetIIHeader::~EthernetIIHeader()
{
}

//==============================================================================
void EthernetIIHeader::addDataFields()
{
    addDataField(&destination);
    addDataField(&source);
    addDataField(&ethertype);
}
