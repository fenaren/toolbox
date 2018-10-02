#include <string>

#include "DataPacket_test1.hpp"

//==============================================================================
DataPacket_test1::DataPacket_test1(const std::string& name) :
    DataPacket(name),
    sdf_int(1, "sdf_int"),
    sdf_double(2.0, "sdf_double"),
    nested_packet("nested_packet")
{
    addDataField(&sdf_int);
    addDataField(&sdf_double);
    addDataField(&nested_packet);
}

//==============================================================================
DataPacket_test1::~DataPacket_test1()
{
}
