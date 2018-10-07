#if !defined DATA_PACKET_TEST2_HPP
#define DATA_PACKET_TEST2_HPP

#include "DataPacket.hpp"

#include "SimpleDataField.hpp"

class DataPacket_test2 : public DataPacket
{
public:

    DataPacket_test2();
    DataPacket_test2(float sdf_float1, float sdf_float2, char sdf_char);

    // Copy constructor
    explicit DataPacket_test2(const DataPacket_test2& dp_test2);

    // Does nothing
    virtual ~DataPacket_test2();

    void setSdfFloat1(float sdf_float1);
    float getSdfFloat1() const;

    void setSdfFloat2(float sdf_float2);
    float getSdfFloat2() const;

    void setSdfChar(char sdf_char);
    char getSdfChar() const;

    DataPacket_test2& operator=(const DataPacket_test2& dp_test2);

private:

    virtual void addDataFields();

    SimpleDataField<float> sdf_float1;
    SimpleDataField<float> sdf_float2;
    SimpleDataField<char>  sdf_char;
};

inline void DataPacket_test2::setSdfFloat1(float sdf_float1)
{
    this->sdf_float1 = sdf_float1;
}

inline float DataPacket_test2::getSdfFloat1() const
{
    return sdf_float1;
}

inline void DataPacket_test2::setSdfFloat2(float sdf_float2)
{
    this->sdf_float2 = sdf_float2;
}

inline float DataPacket_test2::getSdfFloat2() const
{
    return sdf_float2;
}

inline void DataPacket_test2::setSdfChar(char sdf_char)
{
    this->sdf_char = sdf_char;
}

inline char DataPacket_test2::getSdfChar() const
{
    return sdf_char;
}

#endif
