#include <cstdint>

#include "ArpPacket.hpp"

//==============================================================================
ArpPacket::ArpPacket(std::uint8_t hlen, std::uint8_t plen) :
    htype(0),
    ptype(0),
    hlen(hlen),
    plen(plen),
    oper(0),
    sha(hlen),
    spa(plen),
    tha(hlen),
    tpa(plen)
{
    addDataFields();
}

//==============================================================================
ArpPacket::ArpPacket(std::uint16_t htype,
                     std::uint16_t ptype,
                     std::uint8_t  hlen,
                     std::uint8_t  plen,
                     std::uint16_t oper) :
    htype(htype),
    ptype(ptype),
    hlen(hlen),
    plen(plen),
    oper(oper),
    sha(hlen),
    spa(plen),
    tha(hlen),
    tpa(plen)
{
    addDataFields();
}

//==============================================================================
ArpPacket::ArpPacket(std::uint16_t         htype,
                     std::uint16_t         ptype,
                     std::uint8_t          hlen,
                     std::uint8_t          plen,
                     std::uint16_t         oper,
                     const NetworkAddress& sha,
                     const NetworkAddress& spa,
                     const NetworkAddress& tha,
                     const NetworkAddress& tpa) :
    htype(htype),
    ptype(ptype),
    hlen(hlen),
    plen(plen),
    oper(oper),
    sha(sha),
    spa(spa),
    tha(tha),
    tpa(tpa)
{
    addDataFields();
}

//==============================================================================
ArpPacket::ArpPacket(std::uint16_t  htype,
                     std::uint16_t  ptype,
                     std::uint8_t   hlen,
                     std::uint8_t   plen,
                     std::uint16_t  oper,
                     unsigned char* buffer_sha,
                     unsigned char* buffer_spa,
                     unsigned char* buffer_tha,
                     unsigned char* buffer_tpa) :
    htype(htype),
    ptype(ptype),
    hlen(hlen),
    plen(plen),
    oper(oper),
    sha(buffer_sha, hlen),
    spa(buffer_spa, plen),
    tha(buffer_tha, hlen),
    tpa(buffer_tpa, plen)
{
    addDataFields();
}

//==============================================================================
ArpPacket::~ArpPacket()
{
}

//==============================================================================
void ArpPacket::addDataFields()
{
    addDataField(&htype);
    addDataField(&ptype);
    addDataField(&hlen);
    addDataField(&plen);
    addDataField(&oper);
    addDataField(&sha);
    addDataField(&spa);
    addDataField(&tha);
    addDataField(&tpa);
}
