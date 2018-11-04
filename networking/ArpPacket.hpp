#if !defined ARP_PACKET_HPP
#define ARP_PACKET_HPP

#include <cstdint>

#include "ArpPacketBase.hpp"

#include "DataField.hpp"
#include "NetworkAddress.hpp"
#include "SimpleDataField.hpp"

class ArpPacket : public ArpPacketBase
{
public:

    // Constructs an ARP packet with the minimum amount of information provided
    // up-front; the hardware and protocol lengths have to be known because they
    // define the length of their associated fields.  Memory for address and
    // protocol fields is dynamically allocated.
    ArpPacket(std::uint8_t hlen, std::uint8_t plen);

    // Similar to the constructor declared above but allows the rest of the
    // simple fields to be specified
    ArpPacket(std::uint16_t htype,
              std::uint16_t ptype,
              std::uint8_t  hlen,
              std::uint8_t  plen,
              std::uint16_t oper);

    // Constructs an ARP packet by copying externally-provided ARP packet data.
    // This may involve dynamic memory allocation depending on how the
    // NetworkAddress copy constructor is defined.
    ArpPacket(std::uint16_t         htype,
              std::uint16_t         ptype,
              std::uint8_t          hlen,
              std::uint8_t          plen,
              std::uint16_t         oper,
              const NetworkAddress& sha,
              const NetworkAddress& spa,
              const NetworkAddress& tha,
              const NetworkAddress& tpa);

    // Constructs an ARP packet using hardware and protocol field memory that
    // can be maintained either internally or externally.
    ArpPacket(std::uint16_t  htype,
              std::uint16_t  ptype,
              std::uint8_t   hlen,
              std::uint8_t   plen,
              std::uint16_t  oper,
              unsigned char* buffer_sha,
              unsigned char* buffer_spa,
              unsigned char* buffer_tha,
              unsigned char* buffer_tpa,
              bool           owned_sha = true,
              bool           owned_spa = true,
              bool           owned_tha = true,
              bool           owned_tpa = true);

    // Does nothing
    virtual ~ArpPacket();

    // Accessors
    NetworkAddress* getSha();
    NetworkAddress* getSpa();
    NetworkAddress* getTha();
    NetworkAddress* getTpa();

    // Const accessors
    const NetworkAddress* getSha() const;
    const NetworkAddress* getSpa() const;
    const NetworkAddress* getTha() const;
    const NetworkAddress* getTpa() const;

private:

    virtual void addDataFields();

    NetworkAddress sha;
    NetworkAddress spa;
    NetworkAddress tha;
    NetworkAddress tpa;
};

inline NetworkAddress* ArpPacket::getSha()
{
    return &sha;
}

inline NetworkAddress* ArpPacket::getSpa()
{
    return &spa;
}

inline NetworkAddress* ArpPacket::getTha()
{
    return &tha;
}

inline NetworkAddress* ArpPacket::getTpa()
{
    return &tpa;
}

inline const NetworkAddress* ArpPacket::getSha() const
{
    return &sha;
}

inline const NetworkAddress* ArpPacket::getSpa() const
{
    return &spa;
}

inline const NetworkAddress* ArpPacket::getTha() const
{
    return &tha;
}

inline const NetworkAddress* ArpPacket::getTpa() const
{
    return &tpa;
}

#endif
