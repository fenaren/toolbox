#include <cstdint>
#include <cstring>
#include <iostream>

#include "DataPacket_test.hpp"

#include "DataPacket.hpp"
#include "DataPacket_test1.hpp"
#include "DataPacket_test2.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(DataPacket_test)

//==============================================================================
void DataPacket_test::addTestCases()
{
    ADD_TEST_CASE(ReadRaw);
    ADD_TEST_CASE(WriteRawConst);
    ADD_TEST_CASE(GetLengthBits);
}

//==============================================================================
void DataPacket_test::GetLengthBits::addTestCases()
{
    ADD_TEST_CASE(Align1Byte);
    ADD_TEST_CASE(Align2Byte);
    ADD_TEST_CASE(Align3Byte);
    ADD_TEST_CASE(Align4Byte);
}

//==============================================================================
Test::Result DataPacket_test::ReadRaw::body()
{
    DataPacket_test1 dp1;
    DataPacket_test2* dp2 = dp1.getNestedPacket();

    dp1.setAlignment(3);
    dp2->setAlignment(3);

    // Set dp to some arbitrarily-chosen values.  We know what these values are
    // and can test for them later.
    dp1.setSdfInt(0);
    dp1.setSdfDouble(0.0);
    dp2->setSdfFloat1(0.0f);
    dp2->setSdfFloat2(0.0f);
    dp2->setSdfChar(0);

    // We're going to manually set up this memory with the known values defined
    // below, have the packet read it in, and then check that they match
    std::uint8_t* raw_dp1 = new std::uint8_t[dp1.getLengthBytes()];

    int    dp1_int    = 3;
    double dp1_double = 4.0;
    float  dp2_float1 = 1.0f;
    float  dp2_float2 = 2.0f;
    char   dp2_char   = 'A';

    unsigned int offset = 0;

    // Grab sdf_int; it should be at the very beginning of the raw packet
    offset += pushField(raw_dp1, dp1_int, offset);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab sdf_double; it should be right after sdf_int, which means an offset
    // of sizeof(int)
    offset += pushField(raw_dp1, dp1_double, offset);

    // Should be 1 byte of padding here
    offset += 1;

    // Grab sdf_float1 from the nested packet; it should be right after all the
    // fields in the top-level packet, since we're still aligned on 4 bytes
    offset += pushField(raw_dp1, dp2_float1, offset);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab the character out of the nested packet and push an updated and
    // byteswapped copy of it into its place.  readRaw() will read this out
    // later, hopefully correctly.
    offset += pushField(raw_dp1, dp2_float2, offset);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab the character out of the nested packet and push an updated and
    // byteswapped copy of it into its place.  readRaw() will read this out
    // later, hopefully correctly.
    pushField(raw_dp1, dp2_char, offset);

    // Now read the field with the functionality under test
    dp1.DataField::readRaw(raw_dp1);

    // All the values we copied out of the raw packet have to match the values
    // we originally set them to
    MUST_BE_TRUE(dp1_int    == dp1.getSdfInt());
    MUST_BE_TRUE(dp1_double == dp1.getSdfDouble());
    MUST_BE_TRUE(dp2_float1 == dp2->getSdfFloat1());
    MUST_BE_TRUE(dp2_float2 == dp2->getSdfFloat2());
    MUST_BE_TRUE(dp2_char   == dp2->getSdfChar());

    delete [] raw_dp1;

    return Test::PASSED;
}

//==============================================================================
Test::Result DataPacket_test::WriteRawConst::body()
{
    DataPacket_test1 dp1;
    DataPacket_test2* dp2 = dp1.getNestedPacket();

    dp1.setAlignment(3);
    dp2->setAlignment(3);

    // Set dp to some arbitrarily-chosen values.  We know what these values are
    // and can test for them later.
    dp1.setSdfInt(3);
    dp1.setSdfDouble(4.0);
    dp2->setSdfFloat1(1.0f);
    dp2->setSdfFloat2(2.0f);
    dp2->setSdfChar('A');

    // Write out dp1 with a 3-byte alignment and make sure it looks
    // alright.  Write is done in host byte order.
    std::uint8_t* raw_dp1 = new std::uint8_t[dp1.getLengthBytes()];
    dp1.DataField::writeRaw(raw_dp1);

    unsigned int offset = 0;

    // Grab sdf_int; it should be at the very beginning of the raw packet
    int dp1_int;
    offset += pullField(dp1_int, raw_dp1, offset);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab sdf_double; it should be right after sdf_int, which means an offset
    // of sizeof(int)
    double dp1_double;
    offset += pullField(dp1_double, raw_dp1, offset);

    // Should be 1 byte of padding here
    offset += 1;

    // Grab sdf_float1 from the nested packet; it should be right after all the
    // fields in the top-level packet, since we're still aligned on 4 bytes
    float dp2_float1;
    offset += pullField(dp2_float1, raw_dp1, offset);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab the character out of the nested packet and push an updated and
    // byteswapped copy of it into its place.  readRaw() will read this out
    // later, hopefully correctly.
    float dp2_float2;
    offset += pullField(dp2_float2, raw_dp1, offset);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab the character out of the nested packet and push an updated and
    // byteswapped copy of it into its place.  readRaw() will read this out
    // later, hopefully correctly.
    char dp2_char;
    pullField(dp2_char, raw_dp1, offset);

    // All the values we copied out of the raw packet have to match the values
    // we originally set them to
    MUST_BE_TRUE(dp1_int    == dp1.getSdfInt());
    MUST_BE_TRUE(dp1_double == dp1.getSdfDouble());
    MUST_BE_TRUE(dp2_float1 == dp2->getSdfFloat1());
    MUST_BE_TRUE(dp2_float2 == dp2->getSdfFloat2());
    MUST_BE_TRUE(dp2_char   == dp2->getSdfChar());

    delete [] raw_dp1;

    return Test::PASSED;
}

//==============================================================================
Test::Result DataPacket_test::GetLengthBits::Align1Byte::body()
{
    DataPacket_test1 dp1;
    DataPacket_test2* dp2 = dp1.getNestedPacket();

    dp1.setAlignment(1);
    dp2->setAlignment(1);
    std::cout << "Packet length (1-byte align): " << dp1.getLengthBytes()
              << "\n";

    // The right side of the equality operator represents the known sum total of
    // all the sizes in the packet.  There are five total "leaf" fields of types
    // int, double, and float (3 of these).  The total packet length should
    // equal the sum of these when byte alignment is set to 1 byte.
    MUST_BE_TRUE(
        dp1.getLengthBytes() ==
        sizeof(int) + sizeof(double) + (2 * sizeof(float)) + sizeof(char));

    return Test::PASSED;
}

//==============================================================================
Test::Result DataPacket_test::GetLengthBits::Align2Byte::body()
{
    DataPacket_test1 dp1;
    DataPacket_test2* dp2 = dp1.getNestedPacket();

    dp1.setAlignment(2);
    dp2->setAlignment(2);
    std::cout << "Packet length (2-byte align): " << dp1.getLengthBytes()
              << "\n";

    // For a byte alignment of two the total packet size will be different.  The
    // types are the same but some fields should have padding afterwards which
    // will increase the total packet length.  The top-level packet is already
    // aligned on 2 bytes, but the nested packet isn't and should include a byte
    // of padding at the end.
    MUST_BE_TRUE(
        dp1.getLengthBytes() ==
        sizeof(int) + sizeof(double) + (2 * sizeof(float)) + sizeof(char) + 1);

    return Test::PASSED;
}

//==============================================================================
Test::Result DataPacket_test::GetLengthBits::Align3Byte::body()
{
    DataPacket_test1 dp1;
    DataPacket_test2* dp2 = dp1.getNestedPacket();

    dp1.setAlignment(3);
    dp2->setAlignment(3);
    std::cout << "Packet length (3-byte align): " << dp1.getLengthBytes()
              << "\n";

    // Byte alignment of 3 isn't used much but makes a good test.  There should
    // immediately be 2 bytes of padding after the first field,
    MUST_BE_TRUE(
        dp1.getLengthBytes() ==
        sizeof(int) + sizeof(double) + (2 * sizeof(float)) + sizeof(char) + 9);

    return Test::PASSED;
}

//==============================================================================
Test::Result DataPacket_test::GetLengthBits::Align4Byte::body()
{
    DataPacket_test1 dp1;
    DataPacket_test2* dp2 = dp1.getNestedPacket();

    dp1.setAlignment(4);
    dp2->setAlignment(4);
    std::cout << "Packet length (4-byte align): " << dp1.getLengthBytes()
              << "\n";

    // For a byte alignment of four things are mostly the same as a byte
    // alignment of two, but the nested packet needs 3 bytes of padding
    // afterwards
    MUST_BE_TRUE(
        dp1.getLengthBytes() ==
        sizeof(int) + sizeof(double) + (2 * sizeof(float)) + sizeof(char) + 3);

    return Test::PASSED;
}

//==============================================================================
template <class T>
unsigned int DataPacket_test::pullField(T&            dptest_var,
                                        std::uint8_t* raw_dptest,
                                        unsigned int  offset)
{
    // Pull a field from the raw packet and swap to make it legible
    memcpy(&dptest_var, raw_dptest + offset, sizeof(T));

    // Bump this for successive calls
    return sizeof(T);
}

//==============================================================================
template <class T>
unsigned int DataPacket_test::pushField(std::uint8_t* raw_dptest,
                                        T&            dptest_var,
                                        unsigned int  offset)
{
    // Pull a field from the raw packet and swap to make it legible
    memcpy(raw_dptest + offset,
           reinterpret_cast<std::uint8_t*>(&dptest_var),
           sizeof(T));

    // Bump this for successive calls
    return sizeof(T);
}
