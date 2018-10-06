#include "DataPacket_test1.hpp"

//==============================================================================
DataPacket_test1::DataPacket_test1() :
    DataPacket(),
    sdf_int(1),
    sdf_double(2.0),
    nested_packet()
{
    addDataFields();
}

//==============================================================================
// Copy constructor
//==============================================================================
DataPacket_test1::DataPacket_test1(const DataPacket_test1& dp_test1) :
    DataPacket()
{
    addDataFields();

    // Use operator=
    *this = dp_test1;
}

//==============================================================================
DataPacket_test1::~DataPacket_test1()
{
}

//==============================================================================
DataPacket_test1& DataPacket_test1::operator=(const DataPacket_test1& dp_test1)
{
    if (this != &dp_test1)
    {
        sdf_int    = dp_test1.getSdfInt();
        sdf_double = dp_test1.getSdfDouble();

        dp_test1.getNestedPacket(nested_packet);
    }

    return *this;
}

//==============================================================================
void DataPacket_test1::addDataFields()
{
    addDataField(&sdf_int);
    addDataField(&sdf_double);
    addDataField(&nested_packet);
}
