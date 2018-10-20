#include <cstdint>
#include <cstring>

#include "ArpPacketEthernetIpv4.hpp"

#include "misc.hpp"

//==============================================================================
// Constructs an ARP packet (Ethernet and IPv4 variant).  All memory is
// statically allocated.
//==============================================================================
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4() :
    ArpPacket(HTYPE,
              PTYPE,
              HLEN,
              PLEN,
              0,
              sha,
              spa,
              tha,
              tpa,
              false,
              false,
              false,
              false)
{
    initializeAddresses();
}

//==============================================================================
// Allows up-front specification of the OPER field.  All memory is statically
// allocated.
//==============================================================================
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4(std::uint16_t oper) :
    ArpPacket(HTYPE,
              PTYPE,
              HLEN,
              PLEN,
              oper,
              sha,
              spa,
              tha,
              tpa,
              false,
              false,
              false,
              false)
{
    initializeAddresses();
}

//==============================================================================
// Constructs an ARP packet by calling readRaw() on the provided buffer.  No
// byteswapping is performed.
//==============================================================================
// cppcheck-suppress uninitMemberVar
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4(unsigned char* buffer) :
    ArpPacket(HTYPE,
              PTYPE,
              HLEN,
              PLEN,
              0,
              sha,
              spa,
              tha,
              tpa,
              false,
              false,
              false,
              false)
{
    readRaw(buffer);
}

//==============================================================================
// Constructs an ARP packet by calling readRaw() on the provided buffer.
// Byteswapping is performed if needed.
//==============================================================================
// cppcheck-suppress uninitMemberVar
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4(unsigned char*  buffer,
                                             misc::ByteOrder byte_order) :
    ArpPacket(HTYPE,
              PTYPE,
              HLEN,
              PLEN,
              0,
              sha,
              spa,
              tha,
              tpa,
              false,
              false,
              false,
              false)
{
    readRaw(buffer, byte_order);
}

//==============================================================================
ArpPacketEthernetIpv4::~ArpPacketEthernetIpv4()
{
}

//==============================================================================
// Initializes the four address memory blocks
//==============================================================================
void ArpPacketEthernetIpv4::initializeAddresses()
{
    memset(sha, 0, HLEN);
    memset(spa, 0, PLEN);
    memset(tha, 0, HLEN);
    memset(tpa, 0, PLEN);
}
