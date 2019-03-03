#if !defined ARP_PACKET_HPP
#define ARP_PACKET_HPP

#include <cstdint>

#include "ArpPacketBase.hpp"

#include "DataField.hpp"
#include "RawDataField.hpp"
#include "SimpleDataField.hpp"

class ArpPacket : public ArpPacketBase
{
public:

    // Similar to the constructor below but allows the rest of the simple fields
    // to be specified.
    ArpPacket(std::uint16_t htype,
              std::uint16_t ptype,
              std::uint8_t  hlen,
              std::uint8_t  plen,
              std::uint16_t oper);

    // Constructs an ARP packet with the minimum amount of information provided
    // up-front; the hardware and protocol lengths have to be known because they
    // define the length of their associated fields.  Memory for address and
    // protocol fields is dynamically allocated.
    ArpPacket(std::uint8_t hlen, std::uint8_t plen);

    // Constructs an ARP packet by copying externally-provided ARP packet data.
    // This may involve dynamic memory allocation depending on how the
    // RawDataField copy constructor is defined.
    ArpPacket(std::uint16_t       htype,
              std::uint16_t       ptype,
              std::uint8_t        hlen,
              std::uint8_t        plen,
              std::uint16_t       oper,
              const RawDataField& sha,
              const RawDataField& spa,
              const RawDataField& tha,
              const RawDataField& tpa);

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
    RawDataField* getSha();
    RawDataField* getSpa();
    RawDataField* getTha();
    RawDataField* getTpa();

    // Const accessors
    const RawDataField* getSha() const;
    const RawDataField* getSpa() const;
    const RawDataField* getTha() const;
    const RawDataField* getTpa() const;

private:

    void addDataFields();

    RawDataField sha;
    RawDataField spa;
    RawDataField tha;
    RawDataField tpa;

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    ArpPacket(const ArpPacket&);
    ArpPacket& operator=(const ArpPacket&);
};

//==============================================================================
inline RawDataField* ArpPacket::getSha()
{
    return &sha;
}

//==============================================================================
inline RawDataField* ArpPacket::getSpa()
{
    return &spa;
}

//==============================================================================
inline RawDataField* ArpPacket::getTha()
{
    return &tha;
}

//==============================================================================
inline RawDataField* ArpPacket::getTpa()
{
    return &tpa;
}

//==============================================================================
inline const RawDataField* ArpPacket::getSha() const
{
    return &sha;
}

//==============================================================================
inline const RawDataField* ArpPacket::getSpa() const
{
    return &spa;
}

//==============================================================================
inline const RawDataField* ArpPacket::getTha() const
{
    return &tha;
}

//==============================================================================
inline const RawDataField* ArpPacket::getTpa() const
{
    return &tpa;
}

#endif
