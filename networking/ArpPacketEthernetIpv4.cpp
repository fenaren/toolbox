#include <cstdint>
#include <cstring>

#include "ArpPacketEthernetIpv4.hpp"

#include "Ipv4Address.hpp"
#include "MacAddress.hpp"
#include "misc.hpp"

//==============================================================================
// Constructs an ARP packet (Ethernet and IPv4 variant).  All memory is
// statically allocated.  HTYPE, PTYPE, HLEN, and PLEN are set to what they
// should be set to for this variant of ARP
// packet.
//==============================================================================

ArpPacketEthernetIpv4::ArpPacketEthernetIpv4(std::uint16_t oper) :
    ArpPacketBase(HTYPE, PTYPE, HLEN, PLEN, oper)
{
    addDataFields();
}

//==============================================================================
// Allows up-front specification of all the field in this ArpPacket variant
// which should be specifiable.  HTYPE, PTYPE, HLEN, and PLEN are set to what
// they should be set to for this variant of ARP packet.  All memory is
// statically allocated.
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
// Allows up-front specification of all the field in this ArpPacket variant
// which should be specifiable.  HTYPE, PTYPE, HLEN, and PLEN are set to what
// they should be set to for this variant of ARP packet.  All memory is
// statically allocated; data in buffer_* arguments is copied into internal
// storage.
//==============================================================================
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4(std::uint16_t  oper,
                                             unsigned char* buffer_sha,
                                             unsigned char* buffer_spa,
                                             unsigned char* buffer_tha,
                                             unsigned char* buffer_tpa) :
    ArpPacketBase(HTYPE, PTYPE, HLEN, PLEN, oper),
    sha(buffer_sha),
    spa(buffer_spa),
    tha(buffer_tha),
    tpa(buffer_tpa)
{
    addDataFields();
}

//==============================================================================
// Constructs an ARP packet by calling readRaw() on the provided buffer.  No
// byteswapping is performed.
//==============================================================================
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4(unsigned char* buffer) :
    ArpPacketBase(HTYPE, PTYPE, HLEN, PLEN, 0)
{
    addDataFields();

    DataField::readRaw(buffer);
}

//==============================================================================
// Constructs an ARP packet by calling readRaw() on the provided buffer.
// Byteswapping is performed if needed.
//==============================================================================
// cppcheck-suppress uninitMemberVar
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4(unsigned char*  buffer,
                                             misc::ByteOrder byte_order) :
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
