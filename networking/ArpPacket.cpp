#include <cstdint>
#include <stdexcept>

#include "ArpPacket.hpp"

#include "NetworkAddress.hpp"

//==============================================================================
// Constructs an ARP packet with the minimum amount of information provided
// up-front; the hardware and protocol lengths have to be known because they
// define the length of their associated fields.  Memory for address and
// protocol fields is dynamically allocated.
//==============================================================================
ArpPacket::ArpPacket(std::uint8_t hlen, std::uint8_t plen) :
    ArpPacketBase(0, 0, hlen, plen, 0),
    sha(hlen),
    spa(plen),
    tha(hlen),
    tpa(plen)
{
    addDataFields();
}

//==============================================================================
// Constructs an ARP packet in such a way that memory for the hardware and
// protocol fields are dynamically allocated and maintained internally.
//==============================================================================
ArpPacket::ArpPacket(std::uint16_t htype,
                     std::uint16_t ptype,
                     std::uint8_t  hlen,
                     std::uint8_t  plen,
                     std::uint16_t oper) :
    ArpPacketBase(htype, ptype, hlen, plen, oper),
    sha(hlen),
    spa(plen),
    tha(hlen),
    tpa(plen)
{
    addDataFields();
}

//==============================================================================
// Constructs an ARP packet by dynamically allocating memory and copying
// provided NetworkAddress data into them.
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
// Constructs an ARP packet using hardware and protocol field memory that can be
// maintained either internally or externally.
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
    sha(buffer_sha, hlen, owned_sha),
    spa(buffer_spa, plen, owned_spa),
    tha(buffer_tha, hlen, owned_tha),
    tpa(buffer_tpa, plen, owned_tpa)
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
