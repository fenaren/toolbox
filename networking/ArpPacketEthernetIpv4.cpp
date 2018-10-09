#include <cstdint>

#include "ArpPacketEthernetIpv4.hpp"

//==============================================================================
// Constructs an ARP packet (Ethernet and IPv4 variant).  All memory is
// statically allocated.
//==============================================================================
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4() :
    ArpPacket(HTYPE, PTYPE, HLEN, PLEN, 0, sha, spa, tha, tpa)
{
}

//==============================================================================
// Allows up-front specification of the OPER field.  All memory is statically
// allocated.
//==============================================================================
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4(std::uint16_t oper) :
    ArpPacket(HTYPE, PTYPE, HLEN, PLEN, oper, sha, spa, tha, tpa)
{
}

//==============================================================================
ArpPacketEthernetIpv4::~ArpPacketEthernetIpv4()
{
}
