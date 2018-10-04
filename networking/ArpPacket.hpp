#if !defined ARP_PACKET_HPP
#define ARP_PACKET_HPP

#include <cstdint>

#include "DataPacket.hpp"

#include "DataField.hpp"
#include "NetworkAddress.hpp"
#include "SimpleDataField.hpp"

class ArpPacket : public DataPacket
{
public:

    // We must immediately  know these values to be able to form a concrete ARP
    // packet
    ArpPacket(std::uint8_t hlen, std::uint8_t plen);

    // Does nothing
    virtual ~ArpPacket();

private:

    SimpleDataField<std::uint16_t> htype;
    SimpleDataField<std::uint16_t> ptype;
    SimpleDataField<std::uint8_t>  hlen;
    SimpleDataField<std::uint8_t>  plen;
    SimpleDataField<std::uint16_t> oper;
    NetworkAddress sha;
    NetworkAddress spa;
    NetworkAddress tha;
    NetworkAddress tpa;
};

#endif
