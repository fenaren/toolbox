#if !defined ARP_PACKET_ETHERNET_IPV4_HPP
#define ARP_PACKET_ETHERNET_IPV4_HPP

#include <cstdint>

#include "ArpPacket.hpp"

class ArpPacketEthernetIpv4 : public ArpPacket
{
public:

    // Constructs an ARP packet (Ethernet and IPv4 variant).  All memory is
    // statically allocated.
    ArpPacketEthernetIpv4();

    // Allows up-front specification of the OPER field.  All memory is
    // statically allocated.
    ArpPacketEthernetIpv4(std::uint16_t oper);

    // Does nothing
    virtual ~ArpPacketEthernetIpv4();

    // Constant field values for this specific ARP variant
    static const std::uint16_t HTYPE = 1;
    static const std::uint16_t PTYPE = 2048;
    static const std::uint8_t  HLEN  = 6;
    static const std::uint8_t  PLEN  = 4;

private:

    // Statically-allocated memory used for storing Ethernet and IPv4 addresses;
    // these are used by ArpPacket
    unsigned char sha[HLEN];
    unsigned char spa[PLEN];
    unsigned char tha[HLEN];
    unsigned char tpa[PLEN];
};

#endif
