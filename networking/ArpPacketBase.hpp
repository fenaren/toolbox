#if !defined ARP_PACKET_BASE_HPP
#define ARP_PACKET_BASE_HPP

#include <cstdint>

#include "DataPacket.hpp"

#include "SimpleDataField.hpp"

class ArpPacketBase : public DataPacket
{
public:

    // Initializes everything to 0
    ArpPacketBase();

    // Initializes everything to the given values
    ArpPacketBase(std::uint16_t htype,
                  std::uint16_t ptype,
                  std::uint8_t  hlen,
                  std::uint8_t  plen,
                  std::uint16_t oper);

    virtual ~ArpPacketBase();

    // Accessors
    std::uint16_t getHType() const;
    std::uint16_t getPType() const;
    std::uint8_t  getHLen() const;
    std::uint8_t  getPLen() const;
    std::uint16_t getOper() const;

    // Mutators
    void setHType(std::uint16_t htype);
    void setPType(std::uint16_t ptype);
    void setHLen(std::uint8_t   hlen);
    void setPLen(std::uint8_t   plen);
    void setOper(std::uint16_t  oper);

protected:

    SimpleDataField<std::uint16_t> htype;
    SimpleDataField<std::uint16_t> ptype;
    SimpleDataField<std::uint8_t>  hlen;
    SimpleDataField<std::uint8_t>  plen;
    SimpleDataField<std::uint16_t> oper;

private:

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    ArpPacketBase(const ArpPacketBase&);
    ArpPacketBase& operator=(const ArpPacketBase&);
};

inline std::uint16_t ArpPacketBase::getHType() const
{
    return htype;
}

inline std::uint16_t ArpPacketBase::getPType() const
{
    return ptype;
}

inline std::uint8_t ArpPacketBase::getHLen() const
{
    return hlen;
}

inline std::uint8_t ArpPacketBase::getPLen() const
{
    return plen;
}

inline std::uint16_t ArpPacketBase::getOper() const
{
    return oper;
}

inline void ArpPacketBase::setHType(std::uint16_t htype)
{
    this->htype = htype;
}


inline void ArpPacketBase::setPType(std::uint16_t ptype)
{
    this->ptype = ptype;
}


inline void ArpPacketBase::setHLen(std::uint8_t hlen)
{
    this->hlen = hlen;
}


inline void ArpPacketBase::setPLen(std::uint8_t plen)
{
    this->plen = plen;
}


inline void ArpPacketBase::setOper(std::uint16_t oper)
{
    this->oper = oper;
}

#endif
