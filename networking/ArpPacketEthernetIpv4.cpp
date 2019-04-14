#include <cstdint>
#include <cstring>

#include "ArpPacketEthernetIpv4.hpp"

#include "Ipv4Address.hpp"
#include "MacAddress.hpp"
#include "misc.hpp"

//==============================================================================

ArpPacketEthernetIpv4::ArpPacketEthernetIpv4(std::uint16_t oper) :
    ArpPacketBase(HTYPE, PTYPE, HLEN, PLEN, oper)
{
    addDataFields();
}

//==============================================================================
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4(std::uint16_t      oper,
                                             const MacAddress&  sha,
                                             const Ipv4Address& spa,
                                             const MacAddress&  tha,
                                             const Ipv4Address& tpa) :
    ArpPacketBase(HTYPE, PTYPE, HLEN, PLEN, oper),
    sha(sha),
    spa(spa),
    tha(tha),
    tpa(tpa)
{
    addDataFields();
}

//==============================================================================
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4(std::uint16_t oper,
                                             std::uint8_t* buffer_sha,
                                             std::uint8_t* buffer_spa,
                                             std::uint8_t* buffer_tha,
                                             std::uint8_t* buffer_tpa) :
    ArpPacketBase(HTYPE, PTYPE, HLEN, PLEN, oper),
    sha(buffer_sha),
    spa(buffer_spa),
    tha(buffer_tha),
    tpa(buffer_tpa)
{
    addDataFields();
}

//==============================================================================
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4(std::uint8_t* buffer) :
    ArpPacketBase(HTYPE, PTYPE, HLEN, PLEN, 0)
{
    addDataFields();

    DataField::readRaw(buffer);
}

//==============================================================================
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4(const std::uint8_t* buffer) :
    ArpPacketBase(HTYPE, PTYPE, HLEN, PLEN, 0)
{
    addDataFields();

    DataField::readRaw(buffer);
}

//==============================================================================
// cppcheck-suppress uninitMemberVar
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4(std::uint8_t*   buffer,
                                             misc::ByteOrder byte_order) :
    ArpPacketBase(HTYPE, PTYPE, HLEN, PLEN, 0)
{
    addDataFields();

    readRaw(buffer, byte_order);
}

//==============================================================================
// cppcheck-suppress uninitMemberVar
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4(const std::uint8_t* buffer,
                                             misc::ByteOrder     byte_order) :
    ArpPacketBase(HTYPE, PTYPE, HLEN, PLEN, 0)
{
    addDataFields();

    readRaw(buffer, byte_order);
}

//==============================================================================
ArpPacketEthernetIpv4::~ArpPacketEthernetIpv4()
{
}

//==============================================================================
void ArpPacketEthernetIpv4::addDataFields()
{
    addDataField(&htype);
    addDataField(&ptype);
    addDataField(&hlen);
    addDataField(&plen);
    addDataField(&oper);
    addDataField(&sha);
    addDataField(&spa);
    addDataField(&tha);
    addDataField(&tpa);
}
