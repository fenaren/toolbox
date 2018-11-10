#if !defined ETHERNET_II_HEADER
#define ETHERNET_II_HEADER

#include <cstdint>

#include "DataPacket.hpp"
#include "MacAddress.hpp"
#include "SimpleDataField.hpp"
#include "misc.hpp"

class EthernetIIHeader : public DataPacket
{
public:

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

private:

    virtual void addDataFields();

    MacAddress                     destination;
    MacAddress                     source;
    SimpleDataField<std::uint16_t> ethertype;
};

#endif
