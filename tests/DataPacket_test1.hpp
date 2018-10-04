#if !defined DATA_PACKET_TEST1_HPP
#define DATA_PACKET_TEST1_HPP

#include "DataPacket.hpp"

#include "DataPacket_test2.hpp"
#include "SimpleDataField.hpp"

class DataPacket_test1 : public DataPacket
{
public:

    explicit DataPacket_test1();
    virtual ~DataPacket_test1();

    void setSdfInt(int value);
    int getSdfInt() const;

private:

    SimpleDataField<int>    sdf_int;
    SimpleDataField<double> sdf_double;
    DataPacket_test2        nested_packet;
};

inline void DataPacket_test1::setSdfInt(int value)
{
    sdf_int = value;
}

inline int DataPacket_test1::getSdfInt() const
{
    return sdf_int;
}

#endif
