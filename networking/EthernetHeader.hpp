#if !defined ETHERNET_HEADER
#define ETHERNET_HEADER

#include "DataPacket.hpp"
#include "MacAddress.hpp"
#include "SimpleDataField.hpp"

class EthernetHeader : public DataPacket
{
public:

    EthernetHeader();
    virtual ~EthernetHeader();

private:

    virtual void addDataFields();

    MacAddress                     destination;
    MacAddress                     source;
    SimpleDataField<std::uint16_t> eth_type_or_length;
};

#endif
