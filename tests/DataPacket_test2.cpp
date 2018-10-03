#include <string>

#include "DataPacket_test2.hpp"

//==============================================================================
DataPacket_test2::DataPacket_test2(const std::string& name) :
    DataPacket(name),
    sdf_float1(3.0f, "sdf_float1"),
    sdf_float2(3.0f, "sdf_float2"),
    sdf_float3(3.0f, "sdf_float3")
{
    registerDataField(&sdf_float1);
    registerDataField(&sdf_float2);
    registerDataField(&sdf_float3);
}

//==============================================================================
DataPacket_test2::~DataPacket_test2()
{
}
