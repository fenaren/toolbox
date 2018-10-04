#include "DataPacket_test1.hpp"

//==============================================================================
DataPacket_test1::DataPacket_test1() :
    DataPacket(),
    sdf_int(1),
    sdf_double(2.0),
    nested_packet()
{
    registerDataField("sdf_int",       &sdf_int);
    registerDataField("sdf_double",    &sdf_double);
    registerDataField("nested_packet", &nested_packet);
}

//==============================================================================
DataPacket_test1::~DataPacket_test1()
{
}
