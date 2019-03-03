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
    // statically allocated.  HTYPE, PTYPE, HLEN, and PLEN are set to what they
    // should be set to for this variant of ARP packet.
    explicit ArpPacketEthernetIpv4(std::uint16_t oper = 0);

    // Allows up-front specification of all the field in this ArpPacket variant
    // which should be specifiable.  HTYPE, PTYPE, HLEN, and PLEN are set to
    // what they should be set to for this variant of ARP packet.  All memory is
    // statically allocated.
    ArpPacketEthernetIpv4(std::uint16_t      oper,
                          const MacAddress&  sha,
                          const Ipv4Address& spa,
                          const MacAddress&  tha,
                          const Ipv4Address& tpa);

    // Allows up-front specification of all the field in this ArpPacket variant
    // which should be specifiable.  HTYPE, PTYPE, HLEN, and PLEN are set to
    // what they should be set to for this variant of ARP packet.  All memory is
    // statically allocated; data in buffer_* arguments is copied into internal
    // storage.
    ArpPacketEthernetIpv4(std::uint16_t  oper,
                          unsigned char* buffer_sha,
                          unsigned char* buffer_spa,
                          unsigned char* buffer_tha,
                          unsigned char* buffer_tpa);

    // Constructs an ARP packet by calling readRaw() on the provided buffer.  No
    // byteswapping is performed.
    explicit ArpPacketEthernetIpv4(unsigned char* buffer);

    // Constructs an ARP packet by calling readRaw() on the provided buffer.
    // Byteswapping is performed if needed.
    ArpPacketEthernetIpv4(unsigned char* buffer, misc::ByteOrder byte_order);

    // Does nothing
    virtual ~ArpPacketEthernetIpv4();

    // Accessors
    MacAddress*  getSha();
    Ipv4Address* getSpa();
    MacAddress*  getTha();
    Ipv4Address* getTpa();

    // Const accessors
    const MacAddress*  getSha() const;
    const Ipv4Address* getSpa() const;
    const MacAddress*  getTha() const;
    const Ipv4Address* getTpa() const;

    // Constant field values for this specific ARP variant
    static const std::uint16_t HTYPE = 1;
    static const std::uint16_t PTYPE = 2048;
    static const std::uint8_t  HLEN  = 6;
    static const std::uint8_t  PLEN  = 4;

private:

    void addDataFields();

    // Statically-allocated memory used for storing Ethernet and IPv4 addresses;
    // ArpPacket stores its address memory here
    MacAddress  sha;
    Ipv4Address spa;
    MacAddress  tha;
    Ipv4Address tpa;

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    ArpPacketEthernetIpv4(const ArpPacketEthernetIpv4&);
    ArpPacketEthernetIpv4& operator=(const ArpPacketEthernetIpv4&);
};

inline MacAddress* ArpPacketEthernetIpv4::getSha()
{
    return &sha;
}

inline Ipv4Address* ArpPacketEthernetIpv4::getSpa()
{
    return &spa;
}

inline MacAddress* ArpPacketEthernetIpv4::getTha()
{
    return &tha;
}

inline Ipv4Address* ArpPacketEthernetIpv4::getTpa()
{
    return &tpa;
}

inline const MacAddress* ArpPacketEthernetIpv4::getSha() const
{
    return &sha;
}

inline const Ipv4Address* ArpPacketEthernetIpv4::getSpa() const
{
    return &spa;
}

inline const MacAddress* ArpPacketEthernetIpv4::getTha() const
{
    return &tha;
}

inline const Ipv4Address* ArpPacketEthernetIpv4::getTpa() const
{
    return &tpa;
}

#endif
