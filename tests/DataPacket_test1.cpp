#include <string>

#include "DataPacket_test1.hpp"

//==============================================================================
DataPacket_test1::DataPacket_test1(const std::string& name) :
    DataPacket(name)
{
    addDataField(&sdf_int);
    addDataField(&sdf_double);
}

//==============================================================================
DataPacket_test1::~DataPacket_test1()
{
}
