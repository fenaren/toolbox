#if !defined DATA_PACKET_TEST1_HPP
#define DATA_PACKET_TEST1_HPP

#include "DataPacket.hpp"

#include "DataPacket_test2.hpp"
#include "SimpleDataField.hpp"

class DataPacket_test1 : public DataPacket
{
public:

    DataPacket_test1();

    // Copy constructor
    explicit DataPacket_test1(const DataPacket_test1& dp_test1);

    virtual ~DataPacket_test1();

    void setSdfInt(int sdf_int);
    int getSdfInt() const;

    void setSdfDouble(double sdf_double);
    double getSdfDouble() const;

    // Allow direct access to the nested packet; breaks encapsulation but is
    // necessary for in general for packet use to be efficient
    DataPacket_test2* getNestedPacket();
    const DataPacket_test2* getNestedPacket() const;

    DataPacket_test1& operator=(const DataPacket_test1& dp_test1);

private:

    void addDataFields();

    SimpleDataField<int>    sdf_int;
    SimpleDataField<double> sdf_double;
    DataPacket_test2        nested_packet;
};

inline void DataPacket_test1::setSdfInt(int sdf_int)
{
    this->sdf_int = sdf_int;
}

inline int DataPacket_test1::getSdfInt() const
{
    return sdf_int;
}

inline void DataPacket_test1::setSdfDouble(double sdf_double)
{
    this->sdf_double = sdf_double;
}

inline double DataPacket_test1::getSdfDouble() const
{
    return sdf_double;
}

inline DataPacket_test2* DataPacket_test1::getNestedPacket()
{
    return &nested_packet;
}

inline const DataPacket_test2* DataPacket_test1::getNestedPacket() const
{
    return &nested_packet;
}

#endif
