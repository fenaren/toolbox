#if !defined DATA_PACKET_TEST1_HPP
#define DATA_PACKET_TEST1_HPP

#include <string>

#include "DataPacket.hpp"

#include "DataPacket_test2.hpp"
#include "SimpleDataField.hpp"

class DataPacket_test1 : public DataPacket
{
public:

    explicit DataPacket_test1();
    virtual ~DataPacket_test1();

private:

    SimpleDataField<int>    sdf_int;
    SimpleDataField<double> sdf_double;
    DataPacket_test2        nested_packet;
};

#endif
