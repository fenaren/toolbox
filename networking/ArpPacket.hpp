#if !defined ARP_PACKET_HPP
#define ARP_PACKET_HPP

#include <cstdint>

#include "DataPacket.hpp"

#include "DataField.hpp"
#include "NetworkAddress.hpp"

class ArpPacket : public DataPacket
{
public:

    ArpPacket();
    virtual ~ArpPacket();

private:

    std::uint16_t something;
};

#endif
