#include <cstdint>

#include "ArpPacketBase.hpp"

//==============================================================================
// Initializes everything to 0
//==============================================================================
ArpPacketBase::ArpPacketBase() :
    DataPacket(1), // Always aligned on 1 byte
    htype(0),
    ptype(0),
    hlen(0),
    plen(0),
    oper(0)
{
}

//==============================================================================
// Initializes everything to the given values
//==============================================================================
ArpPacketBase::ArpPacketBase(std::uint16_t htype,
                             std::uint16_t ptype,
                             std::uint8_t  hlen,
                             std::uint8_t  plen,
                             std::uint16_t oper) :
    DataPacket(1), // Always aligned on 1 byte
    htype(htype),
    ptype(ptype),
    hlen(hlen),
    plen(plen),
    oper(oper)
{
}

//==============================================================================
ArpPacketBase::~ArpPacketBase()
{
}
