#include <cstdint>
#include <stdexcept>

#include "ArpPacket.hpp"

#include "ArpPacketBase.hpp"
#include "RawDataField.hpp"

//==============================================================================
ArpPacket::ArpPacket(std::uint16_t htype,
                     std::uint16_t ptype,
                     std::uint8_t  hlen,
                     std::uint8_t  plen,
                     std::uint16_t oper) :
    ArpPacketBase(htype, ptype, hlen, plen, oper),
    sha(hlen, misc::BYTES),
    spa(plen, misc::BYTES),
    tha(hlen, misc::BYTES),
    tpa(plen, misc::BYTES)
{
    addDataFields();
}

//==============================================================================
ArpPacket::ArpPacket(std::uint8_t hlen, std::uint8_t plen) :
    ArpPacket(0, 0, hlen, plen, 0)
{
}

//==============================================================================
ArpPacket::ArpPacket(std::uint16_t       htype,
                     std::uint16_t       ptype,
                     std::uint8_t        hlen,
                     std::uint8_t        plen,
                     std::uint16_t       oper,
                     const RawDataField& sha,
                     const RawDataField& spa,
                     const RawDataField& tha,
                     const RawDataField& tpa) :
    ArpPacketBase(htype, ptype, hlen, plen, oper),
    sha(sha),
    spa(spa),
    tha(tha),
    tpa(tpa)
{
    if (hlen != sha.getLengthBytes())
    {
        throw std::runtime_error("Length of provided sha does not match hlen");
    }

    if (hlen != tha.getLengthBytes())
    {
        throw std::runtime_error("Length of provided tha does not match hlen");
    }

    if (plen != spa.getLengthBytes())
    {
        throw std::runtime_error("Length of provided spa does not match plen");
    }

    if (plen != tpa.getLengthBytes())
    {
        throw std::runtime_error("Length of provided tpa does not match plen");
    }

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
                     unsigned char* buffer_tpa,
                     bool           owned_sha,
                     bool           owned_spa,
                     bool           owned_tha,
                     bool           owned_tpa) :
    ArpPacketBase(htype, ptype, hlen, plen, oper),
    sha(buffer_sha, hlen, misc::BYTES, owned_sha),
    spa(buffer_spa, plen, misc::BYTES, owned_spa),
    tha(buffer_tha, hlen, misc::BYTES, owned_tha),
    tpa(buffer_tpa, plen, misc::BYTES, owned_tpa)
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
