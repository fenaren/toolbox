#include "DataPacket_test2.hpp"

//==============================================================================
DataPacket_test2::DataPacket_test2() :
    DataPacket(),
    sdf_float1(0.0f),
    sdf_float2(0.0f),
    sdf_char(0)
{
    addDataFields();
}

//==============================================================================
DataPacket_test2::DataPacket_test2(
    float sdf_float1, float sdf_float2, char sdf_char) :
    DataPacket(),
    sdf_float1(sdf_float1),
    sdf_float2(sdf_float2),
    sdf_char(sdf_char)
{
    addDataFields();
}

//==============================================================================
// Copy constructor
//==============================================================================
DataPacket_test2::DataPacket_test2(const DataPacket_test2& dp_test2) :
    DataPacket()
{
    addDataFields();

    // Use operator=
    *this = dp_test2;
}

//==============================================================================
DataPacket_test2::~DataPacket_test2()
{
}

//==============================================================================
DataPacket_test2& DataPacket_test2::operator=(const DataPacket_test2& dp_test2)
{
    if (this != &dp_test2)
    {
        sdf_float1 = dp_test2.getSdfFloat1();
        sdf_float2 = dp_test2.getSdfFloat2();
        sdf_char   = dp_test2.getSdfChar();
    }

    return *this;
}

//==============================================================================
void DataPacket_test2::addDataFields()
{
    addDataField(&sdf_float1);
    addDataField(&sdf_float2);
    addDataField(&sdf_char);
}
