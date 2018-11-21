#if !defined ETHERNET_II_HEADER
#define ETHERNET_II_HEADER

#include <cstdint>

#include "DataPacket.hpp"

#include "MacAddress.hpp"
#include "SimpleDataField.hpp"
#include "misc.hpp"

// Represents a simple Ethernet II header, including destination MAC, source
// MAC, and Ethertype.  Does not support 802.1Q VLAN tags.
class EthernetIIHeader : public DataPacket
{
public:

    // Shorthand textual ways of referencing some Ethertypes
    enum Ethertype
    {
        IPV4 = 0x0800,
        ARP  = 0x0806
    };

    // Initializes data members to defaults
    EthernetIIHeader();

    // Initializes ethertype, defaults for the rest
    // cppcheck-suppress noExplicitConstructor
    EthernetIIHeader(std::uint16_t ethertype);

    // Initializes all fields
    EthernetIIHeader(const MacAddress& destination,
                     const MacAddress& source,
                     std::uint16_t     ethertype);

    // Constructs an EthernetIIHeader by calling readRaw() on the provided
    // buffer.  No byteswapping is performed.
    explicit EthernetIIHeader(const unsigned char* buffer);

    // Constructs an EthernetIIHeader by calling readRaw() on the provided
    // buffer.  Byteswapping is performed if needed.
    EthernetIIHeader(const unsigned char* buffer, misc::ByteOrder byte_order);

    // Does nothing
    virtual ~EthernetIIHeader();

    MacAddress* getMacDestination();
    const MacAddress* getMacDestination() const;

    MacAddress* getMacSource();
    const MacAddress* getMacSource() const;

    std::uint16_t getEthertype() const;
    void setEthertype(std::uint16_t ethertype);

    // Ethernet II headers without 802.1Q VLAN tags are always exactly this size
    static const unsigned short LENGTH_BYTES = 14;

private:

    virtual void addDataFields();

    MacAddress                     destination;
    MacAddress                     source;
    SimpleDataField<std::uint16_t> ethertype;

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    EthernetIIHeader(const EthernetIIHeader&);
    EthernetIIHeader& operator=(const EthernetIIHeader&);
};

inline MacAddress* EthernetIIHeader::getMacDestination()
{
    return &destination;
}

inline const MacAddress* EthernetIIHeader::getMacDestination() const
{
    return &destination;
}

inline MacAddress* EthernetIIHeader::getMacSource()
{
    return &source;
}

inline const MacAddress* EthernetIIHeader::getMacSource() const
{
    return &source;
}

inline std::uint16_t EthernetIIHeader::getEthertype() const
{
    return ethertype;
}

inline void EthernetIIHeader::setEthertype(std::uint16_t ethertype)
{
    this->ethertype = ethertype;
}

#endif
