#if !defined DATA_PACKET_TEST2_HPP
#define DATA_PACKET_TEST2_HPP

#include <string>

#include "DataPacket.hpp"

#include "SimpleDataField.hpp"

class DataPacket_test2 : public DataPacket
{
public:

    explicit DataPacket_test2(const std::string& name = "");
    virtual ~DataPacket_test2();

private:

    SimpleDataField<float> sdf_float;
};

#endif
