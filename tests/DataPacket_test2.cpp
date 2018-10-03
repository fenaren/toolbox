#include "DataPacket_test2.hpp"

//==============================================================================
DataPacket_test2::DataPacket_test2() :
    DataPacket(),
    sdf_float1(3.0f),
    sdf_float2(3.0f),
    sdf_char('A')
{
    registerDataField("sdf_float1", &sdf_float1);
    registerDataField("sdf_float2", &sdf_float2);
    registerDataField("sdf_char",   &sdf_char);
}

//==============================================================================
DataPacket_test2::~DataPacket_test2()
{
}
