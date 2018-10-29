#if !defined ARP_PACKET_HPP
#define ARP_PACKET_HPP

#include <cstdint>

#include "DataPacket.hpp"

#include "DataField.hpp"
#include "NetworkAddress.hpp"
#include "SimpleDataField.hpp"

class ArpPacket : public DataPacket
{
public:

    // Constructs an ARP packet with the minimum amount of information provided
    // up-front; the hardware and protocol lengths have to be known because they
    // define the length of their associated fields.  Memory for address and
    // protocol fields is dynamically allocated.
    ArpPacket(std::uint8_t hlen, std::uint8_t plen);

    // Constructs an ARP packet in such a way that memory for the hardware and
    // protocol fields are dynamically allocated and maintained internally.
    ArpPacket(std::uint16_t htype,
              std::uint16_t ptype,
              std::uint8_t  hlen,
              std::uint8_t  plen,
              std::uint16_t oper);

    // Constructs an ARP packet by dynamically allocating memory and copying
    // provided NetworkAddresses into them.
    ArpPacket(std::uint16_t   htype,
              std::uint16_t   ptype,
              std::uint8_t    hlen,
              std::uint8_t    plen,
              std::uint16_t   oper,
              NetworkAddress* sha,
              NetworkAddress* spa,
              NetworkAddress* tha,
              NetworkAddress* tpa,
              bool            network_address_owned_sha = true,
              bool            network_address_owned_spa = true,
              bool            network_address_owned_tha = true,
              bool            network_address_owned_tpa = true);

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
              bool           network_address_raw_owned_sha = true,
              bool           network_address_raw_owned_spa = true,
              bool           network_address_raw_owned_tha = true,
              bool           network_address_raw_owned_tpa = true);

    // Does nothing
    virtual ~ArpPacket();

    std::uint16_t getHType() const;
    void setHType(std::uint16_t htype);

    std::uint16_t getPType() const;
    void setPType(std::uint16_t ptype);

    std::uint8_t getHLen() const;
    void setHLen(std::uint8_t hlen);

    std::uint8_t getPLen() const;
    void setPLen(std::uint8_t plen);

    std::uint16_t getOper() const;
    void setOper(std::uint16_t oper);

    NetworkAddress* getSha();
    const NetworkAddress* getSha() const;

    NetworkAddress* getSpa();
    const NetworkAddress* getSpa() const;

    NetworkAddress* getTha();
    const NetworkAddress* getTha() const;

    NetworkAddress* getTpa();
    const NetworkAddress* getTpa() const;

private:

    virtual void addDataFields();

    SimpleDataField<std::uint16_t> htype;
    SimpleDataField<std::uint16_t> ptype;
    SimpleDataField<std::uint8_t>  hlen;
    SimpleDataField<std::uint8_t>  plen;
    SimpleDataField<std::uint16_t> oper;
    NetworkAddress*                sha;
    NetworkAddress*                spa;
    NetworkAddress*                tha;
    NetworkAddress*                tpa;

    bool sha_owned;
    bool spa_owned;
    bool tha_owned;
    bool tpa_owned;
};

inline std::uint16_t ArpPacket::getHType() const
{
    return htype;
}

inline std::uint16_t ArpPacket::getPType() const
{
    return ptype;
}

inline std::uint8_t ArpPacket::getHLen() const
{
    return hlen;
}

inline std::uint8_t ArpPacket::getPLen() const
{
    return plen;
}

inline std::uint16_t ArpPacket::getOper() const
{
    return oper;
}

inline NetworkAddress* ArpPacket::getSha()
{
    return sha;
}

inline const NetworkAddress* ArpPacket::getSha() const
{
    return sha;
}

inline NetworkAddress* ArpPacket::getSpa()
{
    return spa;
}

inline const NetworkAddress* ArpPacket::getSpa() const
{
    return spa;
}

inline NetworkAddress* ArpPacket::getTha()
{
    return tha;
}

inline const NetworkAddress* ArpPacket::getTha() const
{
    return tha;
}

inline NetworkAddress* ArpPacket::getTpa()
{
    return tpa;
}

inline const NetworkAddress* ArpPacket::getTpa() const
{
    return tpa;
}

inline void ArpPacket::setHType(std::uint16_t htype)
{
    this->htype = htype;
}

inline void ArpPacket::setPType(std::uint16_t ptype)
{
    this->ptype = ptype;
}

inline void ArpPacket::setHLen(std::uint8_t hlen)
{
    this->hlen = hlen;
}

inline void ArpPacket::setPLen(std::uint8_t plen)
{
    this->plen = plen;
}

inline void ArpPacket::setOper(std::uint16_t oper)
{
    this->oper = oper;
}

#endif
