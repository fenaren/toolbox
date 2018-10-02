#if !defined DATA_PACKET_TEST_1_HPP
#define DATA_PACKET_TEST_1_HPP

#include <string>

#include "DataPacket.hpp"

#include "SimpleDataField.hpp"

class DataPacket_test_1 : public DataPacket
{
public:

    explicit DataPacket_test_1(const std::string& name = "");
    virtual ~DataPacket_test_1();

private:

    SimpleDataField<int>    sdf_int;
    SimpleDataField<double> sdf_double;
};

#endif
