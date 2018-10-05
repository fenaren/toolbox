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

    // We must immediately know these values to be able to form a concrete ARP
    // packet
    ArpPacket(std::uint8_t hlen, std::uint8_t plen);

    // Does nothing
    virtual ~ArpPacket();

    // Field access
    std::uint16_t getHType() const;
    std::uint16_t getPType() const;
    std::uint8_t getHLen() const;
    std::uint8_t getPLen() const;
    std::uint16_t getOper() const;
    void getSha(NetworkAddress& sha) const;
    void getSpa(NetworkAddress& spa) const;
    void getTha(NetworkAddress& tha) const;
    void getTpa(NetworkAddress& tpa) const;

    // Field mutation
    void setHType(std::uint16_t htype);
    void setPType(std::uint16_t ptype);
    void setHLen(std::uint8_t hlen);
    void setPLen(std::uint8_t plen);
    void setOper(std::uint16_t oper);
    void setSha(const NetworkAddress& sha);
    void setSpa(const NetworkAddress& spa);
    void setTha(const NetworkAddress& tha);
    void setTpa(const NetworkAddress& tpa);

private:

    SimpleDataField<std::uint16_t> htype;
    SimpleDataField<std::uint16_t> ptype;
    SimpleDataField<std::uint8_t> hlen;
    SimpleDataField<std::uint8_t> plen;
    SimpleDataField<std::uint16_t> oper;
    NetworkAddress sha;
    NetworkAddress spa;
    NetworkAddress tha;
    NetworkAddress tpa;
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

inline void ArpPacket::getSha(NetworkAddress& sha) const
{
    sha = this->sha;
}

inline void ArpPacket::getSpa(NetworkAddress& spa) const
{
    spa = this->spa;
}

inline void ArpPacket::getTha(NetworkAddress& tha) const
{
    tha = this->tha;
}

inline void ArpPacket::getTpa(NetworkAddress& tpa) const
{
    tpa = this->tpa;
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

inline void ArpPacket::setSha(const NetworkAddress& sha)
{
    this->sha = sha;
}

inline void ArpPacket::setSpa(const NetworkAddress& spa)
{
    this->spa = spa;
}

inline void ArpPacket::setTha(const NetworkAddress& tha)
{
    this->tha = tha;
}

inline void ArpPacket::setTpa(const NetworkAddress& tpa)
{
    this->tpa = tpa;
}

#endif
