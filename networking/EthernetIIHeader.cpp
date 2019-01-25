#include <cstdint>

#include "EthernetIIHeader.hpp"
#include "misc.hpp"

#include "MacAddress.hpp"

//==============================================================================
// Initializes data members to defaults
//==============================================================================
EthernetIIHeader::EthernetIIHeader() :
    DataPacket(1), // always aligned on 1 byte (no alignment)
    ethertype(0)
{
    addDataFields();
}

//==============================================================================
// Initializes ethertype, defaults for the rest
//==============================================================================
EthernetIIHeader::EthernetIIHeader(std::uint16_t ethertype) :
    EthernetIIHeader()
{
    this->ethertype = ethertype;
}

//==============================================================================
// Initializes all fields
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
// Constructs an EthernetIIHeader by calling readRaw() on the provided buffer.
// No byteswapping is performed.
//==============================================================================
EthernetIIHeader::EthernetIIHeader(std::uint8_t* buffer) :
    EthernetIIHeader()
{
    readRaw(buffer);
}

//==============================================================================
// Constructs an EthernetIIHeader by calling readRaw() on the provided buffer.
// Byteswapping is performed if needed.
//==============================================================================
EthernetIIHeader::EthernetIIHeader(std::uint8_t*   buffer,
                                   misc::ByteOrder byte_order) :
    EthernetIIHeader()
{
    // Ethernet II frames store big endian data by definition
    readRaw(buffer, misc::ENDIAN_BIG);
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
