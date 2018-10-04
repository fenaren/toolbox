#include "DataPacket_test2.hpp"

//==============================================================================
DataPacket_test2::DataPacket_test2() :
    DataPacket(),
    sdf_float1(3.0f),
    sdf_float2(3.0f),
    sdf_char('A')
{
    addDataField(&sdf_float1);
    addDataField(&sdf_float2);
    addDataField(&sdf_char);
}

//==============================================================================
DataPacket_test2::~DataPacket_test2()
{
}
