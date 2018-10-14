#include <cstdint>

#include "ArpPacket.hpp"

#include "MemoryMode.hpp"
#include "NetworkAddress.hpp"

//==============================================================================
// Constructs an ARP packet with the minimum amount of information provided
// up-front; the hardware and protocol lengths have to be known to construct
// their associated fields.  Memory for fields is dynamically allocated.
//==============================================================================
ArpPacket::ArpPacket(std::uint8_t hlen, std::uint8_t plen) :
    DataPacket(1),
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
// Constructs an ARP packet in such a way that memory for the hardware and
// protocol fields are dynamically allocated and maintained internally
//==============================================================================
ArpPacket::ArpPacket(std::uint16_t htype,
                     std::uint16_t ptype,
                     std::uint8_t  hlen,
                     std::uint8_t  plen,
                     std::uint16_t oper) :
    DataPacket(1),
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
    DataPacket(1),
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
// Constructs an ARP packet using hardware and protocol field memory that is
// maintained externally.  This is useful for derived classes for specific
// variants of the ARP packet (for example, Ethernet and IPv4-specific ARP
// packets).
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
                     MemoryMode     memory_mode) :
    DataPacket(1),
    htype(htype),
    ptype(ptype),
    hlen(hlen),
    plen(plen),
    oper(oper),
    sha(buffer_sha, hlen, memory_mode),
    spa(buffer_spa, plen, memory_mode),
    tha(buffer_tha, hlen, memory_mode),
    tpa(buffer_tpa, plen, memory_mode)
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
