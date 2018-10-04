#include "DataPacket_test1.hpp"

//==============================================================================
DataPacket_test1::DataPacket_test1() :
    DataPacket(),
    sdf_int(1),
    sdf_double(2.0),
    nested_packet()
{
    addDataField(&sdf_int);
    addDataField(&sdf_double);
    addDataField(&nested_packet);
}

//==============================================================================
DataPacket_test1::~DataPacket_test1()
{
}
