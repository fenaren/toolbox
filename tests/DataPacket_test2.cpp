#include <string>

#include "DataPacket_test2.hpp"

//==============================================================================
DataPacket_test2::DataPacket_test2(const std::string& name) :
    DataPacket(name)
{
    addDataField(&sdf_float);
}

//==============================================================================
DataPacket_test2::~DataPacket_test2()
{
}
