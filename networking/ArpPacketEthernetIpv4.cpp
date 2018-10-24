#include <cstdint>
#include <cstring>

#include "ArpPacketEthernetIpv4.hpp"

#include "Ipv4Address.hpp"
#include "MacAddress.hpp"
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
              &sha,
              &spa,
              &tha,
              &tpa)
{
}

//==============================================================================
// Allows up-front specification of all the field in this ArpPacket variant
// which should be specifiable.
//==============================================================================
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4(std::uint16_t  oper,
                                             unsigned char* buffer_sha,
                                             unsigned char* buffer_spa,
                                             unsigned char* buffer_tha,
                                             unsigned char* buffer_tpa):
    ArpPacket(HTYPE,
              PTYPE,
              HLEN,
              PLEN,
              oper,
              &sha,
              &spa,
              &tha,
              &tpa)
{
    sha.readRaw(buffer_sha);
    spa.readRaw(buffer_spa);
    tha.readRaw(buffer_tha);
    tpa.readRaw(buffer_tpa);
}

//==============================================================================
// Allows up-front specification of all the field in this ArpPacket variant
// which should be specifiable.
//==============================================================================
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4(std::uint16_t      oper,
                                             const MacAddress&  sha,
                                             const Ipv4Address& spa,
                                             const MacAddress&  tha,
                                             const Ipv4Address& tpa) :
    ArpPacket(HTYPE,
              PTYPE,
              HLEN,
              PLEN,
              0,
              &this->sha,
              &this->spa,
              &this->tha,
              &this->tpa,
              false,
              false,
              false,
              false)
{
}

//==============================================================================
// Constructs an ARP packet by calling readRaw() on the provided buffer.  No
// byteswapping is performed.
//==============================================================================
ArpPacketEthernetIpv4::ArpPacketEthernetIpv4(unsigned char* buffer) :
    ArpPacket(HTYPE,
              PTYPE,
              HLEN,
              PLEN,
              0,
              &sha,
              &spa,
              &tha,
              &tpa)
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
              &sha,
              &spa,
              &tha,
              &tpa)
{
    readRaw(buffer, byte_order);
}

//==============================================================================
ArpPacketEthernetIpv4::~ArpPacketEthernetIpv4()
{
}
