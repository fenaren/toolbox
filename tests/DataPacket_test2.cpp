#include "DataPacket_test2.hpp"

//==============================================================================
DataPacket_test2::DataPacket_test2() :
    DataPacket(),
    sdf_float1(3.0f),
    sdf_float2(3.0f),
    sdf_char('A')
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
