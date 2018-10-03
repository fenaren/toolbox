#if !defined DATA_PACKET_TEST2_HPP
#define DATA_PACKET_TEST2_HPP

#include "DataPacket.hpp"

#include "SimpleDataField.hpp"

class DataPacket_test2 : public DataPacket
{
public:

    explicit DataPacket_test2();
    virtual ~DataPacket_test2();

private:

    SimpleDataField<float> sdf_float1;
    SimpleDataField<float> sdf_float2;
    SimpleDataField<char>  sdf_char;
};

#endif
