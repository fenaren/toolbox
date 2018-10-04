#include <cstdint>

#include "ArpPacket.hpp"

//==============================================================================
ArpPacket::ArpPacket(std::uint8_t hlen, std::uint8_t plen) :
    hlen(hlen),
    plen(plen),
    sha(hlen),
    spa(plen),
    tha(hlen),
    tpa(plen)
{
    addDataField(&htype);
    addDataField(&ptype);
    addDataField(&this->hlen);
    addDataField(&this->plen);
    addDataField(&oper);
    addDataField(&sha);
    addDataField(&spa);
    addDataField(&tha);
    addDataField(&tpa);
}

//==============================================================================
ArpPacket::~ArpPacket()
{
}
