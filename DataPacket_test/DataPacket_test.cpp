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
#include "pullUpdatePush.hpp"

TEST_PROGRAM_MAIN(DataPacket_test)

//==============================================================================
void DataPacket_test::addTestCases()
{
    ADD_TEST_CASE(ReadRaw);
    ADD_TEST_CASE(ReadRawConstBuffer);
    ADD_TEST_CASE(WriteRaw);
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
Test::Result DataPacket_test::GetLengthBits::Align1Byte::body()
{
    return Test::SKIPPED;
}

//==============================================================================
Test::Result DataPacket_test::GetLengthBits::Align2Byte::body()
{
    return Test::SKIPPED;
}

//==============================================================================
Test::Result DataPacket_test::GetLengthBits::Align3Byte::body()
{
    return Test::SKIPPED;
}

//==============================================================================
Test::Result DataPacket_test::GetLengthBits::Align4Byte::body()
{
    return Test::SKIPPED;
}

//==============================================================================
/*Test::Result DataPacket_test::GetLengthBytes_Align1Byte::body()
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
Test::Result DataPacket_test::GetLengthBytes_Align2Byte::body()
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
Test::Result DataPacket_test::GetLengthBytes_Align3Byte::body()
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
Test::Result DataPacket_test::GetLengthBytes_Align4Byte::body()
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
Test::Result DataPacket_test::PullUpdatePush::body()
{
    DataPacket_test1 dp1;
    DataPacket_test2* dp2 = dp1.getNestedPacket();

    dp1.setAlignment(3);
    dp2->setAlignment(3);

    initializeDp(dp1);

    // Write out dp1 with a 3-byte alignment and make sure it looks
    // alright.  Write is done in host byte order.
    std::uint8_t* raw_dp1 = new std::uint8_t[dp1.getLengthBytes()];
    dp1.DataField::writeRaw(raw_dp1);

    unsigned int offset = 0;

    // Grab sdf_int; it should be at the very beginning of the raw packet
    int dp1_int;
    int dp1_int_updated;
    pullUpdatePush(raw_dp1, dp1_int, dp1_int_updated, offset, false);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab sdf_double; it should be right after sdf_int, which means an offset
    // of sizeof(int)
    double dp1_double;
    double dp1_double_updated;
    pullUpdatePush(raw_dp1,
                   dp1_double,
                   dp1_double_updated,
                   offset,
                   false);

    // Should be 1 byte of padding here
    offset += 1;

    // Grab sdf_float1 from the nested packet; it should be right after all the
    // fields in the top-level packet, since we're still aligned on 4 bytes
    float dp2_float1;
    float dp2_float1_updated;
    pullUpdatePush(raw_dp1, dp2_float1, dp2_float1_updated, offset, false);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab the character out of the nested packet and push an updated and
    // byteswapped copy of it into its place.  readRaw() will read this out
    // later, hopefully correctly.
    float dp2_float2;
    float dp2_float2_updated;
    pullUpdatePush(raw_dp1, dp2_float2, dp2_float2_updated, offset, false);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab the character out of the nested packet and push an updated and
    // byteswapped copy of it into its place.  readRaw() will read this out
    // later, hopefully correctly.
    char dp2_char;
    char dp2_char_updated;
    pullUpdatePush(raw_dp1, dp2_char, dp2_char_updated, offset, false);

    // All the values we copied out of the raw packet have to match the values
    // we originally set them to
    MUST_BE_TRUE(dp1_int    == dp1.getSdfInt());
    MUST_BE_TRUE(dp1_double == dp1.getSdfDouble());
    MUST_BE_TRUE(dp2_float1 == dp2->getSdfFloat1());
    MUST_BE_TRUE(dp2_float2 == dp2->getSdfFloat2());
    MUST_BE_TRUE(dp2_char   == dp2->getSdfChar());

    // Read the updated raw data and compare against the updated values
    dp1.DataField::readRaw(raw_dp1);

    // All the values we wrote into the raw packet have to match the values we
    // retrieved after reading the raw packet
    MUST_BE_TRUE(dp1_int_updated    == dp1.getSdfInt());
    MUST_BE_TRUE(dp1_double_updated == dp1.getSdfDouble());
    MUST_BE_TRUE(dp2_float1_updated == dp2->getSdfFloat1());
    MUST_BE_TRUE(dp2_float2_updated == dp2->getSdfFloat2());
    MUST_BE_TRUE(dp2_char_updated   == dp2->getSdfChar());

    delete [] raw_dp1;

    return Test::PASSED;
}

//==============================================================================
Test::Result DataPacket_test::PullUpdatePush_Swap::body()
{
    // We want to know what endianness this host does NOT have so we can force
    // byteswapping from the packet routines
    misc::ByteOrder byteorder_opposite = !misc::getByteOrder();

    DataPacket_test1 dp1;
    DataPacket_test2* dp2 = dp1.getNestedPacket();

    dp1.setAlignment(3);
    dp2->setAlignment(3);

    initializeDp(dp1);

    // Write out dp1 with a 3-byte alignment and make sure it looks
    // alright.  Write is done in whatever byte order this host doesn't have.
    unsigned char* raw_dp1 = new unsigned char[dp1.getLengthBytes()];
    dp1.writeRaw(raw_dp1, byteorder_opposite);

    unsigned int offset = 0;

    // Grab sdf_int; it should be at the very beginning of the raw packet
    int dp1_int;
    int dp1_int_updated;
    pullUpdatePush(raw_dp1, dp1_int, dp1_int_updated, offset, true);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab sdf_double; it should be right after sdf_int, which means an offset
    // of sizeof(int)
    double dp1_double;
    double dp1_double_updated;
    pullUpdatePush(raw_dp1, dp1_double, dp1_double_updated, offset, true);

    // Should be 1 byte of padding here
    offset += 1;

    // Grab sdf_float1 from the nested packet; it should be right after all the
    // fields in the top-level packet, since we're still aligned on 4 bytes
    float dp2_float1;
    float dp2_float1_updated;
    pullUpdatePush(raw_dp1, dp2_float1, dp2_float1_updated, offset, true);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab the character out of the nested packet and push an updated and
    // byteswapped copy of it into its place.  readRaw() will read this out
    // later, hopefully correctly.
    float dp2_float2;
    float dp2_float2_updated;
    pullUpdatePush(raw_dp1, dp2_float2, dp2_float2_updated, offset, true);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab the character out of the nested packet and push an updated and
    // byteswapped copy of it into its place.  readRaw() will read this out
    // later, hopefully correctly.
    char dp2_char;
    char dp2_char_updated;
    pullUpdatePush(raw_dp1, dp2_char, dp2_char_updated, offset, true);

    // All the values we copied out of the raw packet have to match the values
    // we originally set them to
    MUST_BE_TRUE(dp1_int    == dp1.getSdfInt());
    MUST_BE_TRUE(dp1_double == dp1.getSdfDouble());
    MUST_BE_TRUE(dp2_float1 == dp2->getSdfFloat1());
    MUST_BE_TRUE(dp2_float2 == dp2->getSdfFloat2());
    MUST_BE_TRUE(dp2_char   == dp2->getSdfChar());

    // Read the updated raw data and compare against the updated values
    dp1.readRaw(raw_dp1, byteorder_opposite);

    // All the values we wrote into the raw packet have to match the values we
    // retrieved after reading the raw packet
    MUST_BE_TRUE(dp1_int_updated    == dp1.getSdfInt());
    MUST_BE_TRUE(dp1_double_updated == dp1.getSdfDouble());
    MUST_BE_TRUE(dp2_float1_updated == dp2->getSdfFloat1());
    MUST_BE_TRUE(dp2_float2_updated == dp2->getSdfFloat2());
    MUST_BE_TRUE(dp2_char_updated   == dp2->getSdfChar());

    delete [] raw_dp1;

    return Test::PASSED;
}

//==============================================================================
void initializeDp(DataPacket_test1& dp)
{
    dp.setSdfInt(3);
    dp.setSdfDouble(4.0);

    DataPacket_test2* dp2 = dp.getNestedPacket();
    dp2->setSdfFloat1(1.0f);
    dp2->setSdfFloat2(2.0f);
    dp2->setSdfChar('A');
}
*/
