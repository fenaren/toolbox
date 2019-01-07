#if !defined ARP_PACKET_HPP
#define ARP_PACKET_HPP

#include <cstdint>

#include "ArpPacketBase.hpp"

#include "BitField.hpp"
#include "DataField.hpp"
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
    // BitField copy constructor is defined.
    ArpPacket(std::uint16_t   htype,
              std::uint16_t   ptype,
              std::uint8_t    hlen,
              std::uint8_t    plen,
              std::uint16_t   oper,
              const BitField& sha,
              const BitField& spa,
              const BitField& tha,
              const BitField& tpa);

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
    BitField* getSha();
    BitField* getSpa();
    BitField* getTha();
    BitField* getTpa();

    // Const accessors
    const BitField* getSha() const;
    const BitField* getSpa() const;
    const BitField* getTha() const;
    const BitField* getTpa() const;

private:

    virtual void addDataFields();

    BitField sha;
    BitField spa;
    BitField tha;
    BitField tpa;

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    ArpPacket(const ArpPacket&);
    ArpPacket& operator=(const ArpPacket&);
};

inline BitField* ArpPacket::getSha()
{
    return &sha;
}

inline BitField* ArpPacket::getSpa()
{
    return &spa;
}

inline BitField* ArpPacket::getTha()
{
    return &tha;
}

inline BitField* ArpPacket::getTpa()
{
    return &tpa;
}

inline const BitField* ArpPacket::getSha() const
{
    return &sha;
}

inline const BitField* ArpPacket::getSpa() const
{
    return &spa;
}

inline const BitField* ArpPacket::getTha() const
{
    return &tha;
}

inline const BitField* ArpPacket::getTpa() const
{
    return &tpa;
}

#endif
