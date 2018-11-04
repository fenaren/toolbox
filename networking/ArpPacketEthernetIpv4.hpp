#if !defined ARP_PACKET_ETHERNET_IPV4_HPP
#define ARP_PACKET_ETHERNET_IPV4_HPP

#include <cstdint>

#include "ArpPacketBase.hpp"

#include "Ipv4Address.hpp"
#include "MacAddress.hpp"
#include "misc.hpp"

class ArpPacketEthernetIpv4 : public ArpPacketBase
{
public:

    // Constructs an ARP packet (Ethernet and IPv4 variant).  All memory is
    // statically allocated.
    ArpPacketEthernetIpv4(std::uint16_t oper = 0);

    // Allows up-front specification of all the field in this ArpPacket variant
    // which should be specifiable.
    ArpPacketEthernetIpv4(std::uint16_t      oper,
                          const MacAddress&  sha,
                          const Ipv4Address& spa,
                          const MacAddress&  tha,
                          const Ipv4Address& tpa);

    // Allows up-front specification of all the field in this ArpPacket variant
    // which should be specifiable.
    ArpPacketEthernetIpv4(std::uint16_t  oper,
                          unsigned char* buffer_sha,
                          unsigned char* buffer_spa,
                          unsigned char* buffer_tha,
                          unsigned char* buffer_tpa);

    // Constructs an ARP packet by calling readRaw() on the provided buffer.
    explicit ArpPacketEthernetIpv4(unsigned char* buffer);

    // Constructs an ARP packet by calling readRaw() on the provided buffer.
    ArpPacketEthernetIpv4(unsigned char* buffer, misc::ByteOrder byte_order);

    // Does nothing
    virtual ~ArpPacketEthernetIpv4();

    // Constant field values for this specific ARP variant
    static const std::uint16_t HTYPE = 1;
    static const std::uint16_t PTYPE = 2048;
    static const std::uint8_t  HLEN  = 6;
    static const std::uint8_t  PLEN  = 4;

private:

    virtual void addDataFields();

    // Statically-allocated memory used for storing Ethernet and IPv4 addresses;
    // ArpPacket stores its address memory here
    MacAddress  sha;
    Ipv4Address spa;
    MacAddress  tha;
    Ipv4Address tpa;
};

#endif
