#if !defined DATA_PACKET_TEST1_HPP
#define DATA_PACKET_TEST1_HPP

#include "DataPacket.hpp"

#include "DataPacket_test2.hpp"
#include "SimpleDataField.hpp"

class DataPacket_test1 : public DataPacket
{
public:

    explicit DataPacket_test1();
    explicit DataPacket_test1(const DataPacket_test1& dp_test1);

    virtual ~DataPacket_test1();

    void setSdfInt(int sdf_int);
    int getSdfInt() const;

    void setSdfDouble(double sdf_double);
    double getSdfDouble() const;

    void setNestedPacket(const DataPacket_test2& dp_test2);
    void getNestedPacket(DataPacket_test2& dp_test2) const;

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

inline
void DataPacket_test1::setNestedPacket(const DataPacket_test2& nested_packet)
{
    this->nested_packet = nested_packet;
}

inline
void DataPacket_test1::getNestedPacket(DataPacket_test2& nested_packet) const
{
    nested_packet = this->nested_packet;
}

#endif
