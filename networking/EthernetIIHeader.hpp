#if !defined ETHERNET_II_HEADER
#define ETHERNET_II_HEADER

#include "DataPacket.hpp"
#include "MacAddress.hpp"
#include "SimpleDataField.hpp"

class EthernetIIHeader : public DataPacket
{
public:

    EthernetIIHeader();
    virtual ~EthernetIIHeader();

private:

    virtual void addDataFields();

    MacAddress                     destination;
    MacAddress                     source;
    SimpleDataField<std::uint16_t> eth_type_or_length;
};

#endif
