#include <cstdint>
#include <cstring>

#include "ArpPacketEthernetIpv4.hpp"

#include "MemoryMode.hpp"

//==============================================================================
// Constructs an ARP packet (Ethernet and IPv4 variant).  All memory is
// statically allocated.
//==============================================================================
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4() :
    ArpPacket(HTYPE, PTYPE, HLEN, PLEN, 0, sha, spa, tha, tpa, MEMORY_EXTERNAL)
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
              MEMORY_EXTERNAL)
{
    initializeAddresses();
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
