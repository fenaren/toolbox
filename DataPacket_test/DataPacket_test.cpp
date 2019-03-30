#include <cstdint>
#include <cstring>
#include <iostream>

#include "DataPacket.hpp"
#include "DataPacket_test1.hpp"
#include "DataPacket_test2.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"
#include "pullUpdatePush.hpp"

TEST_CASES_PROGRAM_BEGIN(DataPacket_test)
TEST(GetLengthBytes_Align1Byte)
TEST(GetLengthBytes_Align2Byte)
TEST(GetLengthBytes_Align3Byte)
TEST(GetLengthBytes_Align4Byte)
TEST_CASES_PROGRAM_END(DataPacket_test)

void initializeDp(DataPacket_test1& dp);

//==============================================================================
void DataPacket_test::addTestCases()
{
    addTestCase(new GetLengthBytes_Align1Byte());
    addTestCase(new GetLengthBytes_Align2Byte());
    addTestCase(new GetLengthBytes_Align3Byte());
    addTestCase(new GetLengthBytes_Align4Byte());
}

//==============================================================================
Test::Result DataPacket_test::GetLengthBytes_Align1Byte::body()
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
/*
//==============================================================================
Test::Result DataPacket_test_case2::body()
{
    // Initialize with some dummy data; will check for proper byteswappng later
    DataPacket_test2 dptest2(1.0f, 2.0f, 'A');
    DataPacket_test1 dptest1(3, 4.0, dptest2);

    // dptest2 data is copied to here; dptest2 is not referenced again
    DataPacket_test2* dptest2p = dptest1.getNestedPacket();

    dptest1.setAlignment(3);
    dptest2p->setAlignment(3);

    // Write out dptest1 with a 3-byte alignment and make sure it looks
    // alright.  Write is done in host byte order.
    std::uint8_t* raw_dptest1 = new std::uint8_t[dptest1.getLengthBytes()];
    dptest1.DataField::writeRaw(raw_dptest1);

    unsigned int offset = 0;

    // Grab sdf_int; it should be at the very beginning of the raw packet
    int dptest1_int;
    int dptest1_int_updated;
    pullUpdatePush(raw_dptest1,
                   dptest1_int,
                   dptest1_int_updated,
                   offset,
                   false);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab sdf_double; it should be right after sdf_int, which means an offset
    // of sizeof(int)
    double dptest1_double;
    double dptest1_double_updated;
    pullUpdatePush(raw_dptest1,
                   dptest1_double,
                   dptest1_double_updated,
                   offset,
                   false);

    // Should be 1 byte of padding here
    offset += 1;

    // Grab sdf_float1 from the nested packet; it should be right after all the
    // fields in the top-level packet, since we're still aligned on 4 bytes
    float dptest2_float1;
    float dptest2_float1_updated;
    pullUpdatePush(raw_dptest1,
                   dptest2_float1,
                   dptest2_float1_updated,
                   offset,
                   false);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab the character out of the nested packet and push an updated and
    // byteswapped copy of it into its place.  readRaw() will read this out
    // later, hopefully correctly.
    float dptest2_float2;
    float dptest2_float2_updated;
    pullUpdatePush(raw_dptest1,
                   dptest2_float2,
                   dptest2_float2_updated,
                   offset,
                   false);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab the character out of the nested packet and push an updated and
    // byteswapped copy of it into its place.  readRaw() will read this out
    // later, hopefully correctly.
    char dptest2_char;
    char dptest2_char_updated;
    pullUpdatePush(raw_dptest1,
                   dptest2_char,
                   dptest2_char_updated,
                   offset,
                   false);

    // All the values we copied out of the raw packet have to match the values
    // we originally set them to
    MUST_BE_TRUE(dptest1_int    == dptest1.getSdfInt());
    MUST_BE_TRUE(dptest1_double == dptest1.getSdfDouble());
    MUST_BE_TRUE(dptest2_float1 == dptest2p->getSdfFloat1());
    MUST_BE_TRUE(dptest2_float2 == dptest2p->getSdfFloat2());
    MUST_BE_TRUE(dptest2_char   == dptest2p->getSdfChar());

    // Read the updated raw data and compare against the updated values
    dptest1.DataField::readRaw(raw_dptest1);

    // All the values we wrote into the raw packet have to match the values we
    // retrieved after reading the raw packet
    MUST_BE_TRUE(dptest1_int_updated    == dptest1.getSdfInt());
    MUST_BE_TRUE(dptest1_double_updated == dptest1.getSdfDouble());
    MUST_BE_TRUE(dptest2_float1_updated == dptest2p->getSdfFloat1());
    MUST_BE_TRUE(dptest2_float2_updated == dptest2p->getSdfFloat2());
    MUST_BE_TRUE(dptest2_char_updated   == dptest2p->getSdfChar());

    delete [] raw_dptest1;

    return Test::PASSED;
}

//==============================================================================
Test::Result DataPacket_test_case3::body()
{
    // We want to know what endianness this host does NOT have so we can force
    // byteswapping from the packet routines
    misc::ByteOrder byteorder_opposite = !misc::getByteOrder();

    // Initialize with some dummy data; will check for proper byteswappng later
    DataPacket_test2 dptest2(1.0f, 2.0f, 'A');
    DataPacket_test1 dptest1(3, 4.0, dptest2);

    // dptest2 data is copied to here; dptest2 is not referenced again
    DataPacket_test2* dptest2p = dptest1.getNestedPacket();

    dptest1.setAlignment(3);
    dptest2p->setAlignment(3);

    // Write out dptest1 with a 3-byte alignment and make sure it looks
    // alright.  Write is done in whatever byte order this host doesn't have.
    unsigned char* raw_dptest1 = new unsigned char[dptest1.getLengthBytes()];
    dptest1.writeRaw(raw_dptest1, byteorder_opposite);

    unsigned int offset = 0;

    // Grab sdf_int; it should be at the very beginning of the raw packet
    int dptest1_int;
    int dptest1_int_updated;
    pullUpdatePush(raw_dptest1, dptest1_int, dptest1_int_updated, offset, true);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab sdf_double; it should be right after sdf_int, which means an offset
    // of sizeof(int)
    double dptest1_double;
    double dptest1_double_updated;
    pullUpdatePush(raw_dptest1,
                   dptest1_double,
                   dptest1_double_updated,
                   offset,
                   true);

    // Should be 1 byte of padding here
    offset += 1;

    // Grab sdf_float1 from the nested packet; it should be right after all the
    // fields in the top-level packet, since we're still aligned on 4 bytes
    float dptest2_float1;
    float dptest2_float1_updated;
    pullUpdatePush(raw_dptest1,
                   dptest2_float1,
                   dptest2_float1_updated,
                   offset,
                   true);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab the character out of the nested packet and push an updated and
    // byteswapped copy of it into its place.  readRaw() will read this out
    // later, hopefully correctly.
    float dptest2_float2;
    float dptest2_float2_updated;
    pullUpdatePush(raw_dptest1,
                   dptest2_float2,
                   dptest2_float2_updated,
                   offset,
                   true);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab the character out of the nested packet and push an updated and
    // byteswapped copy of it into its place.  readRaw() will read this out
    // later, hopefully correctly.
    char dptest2_char;
    char dptest2_char_updated;
    pullUpdatePush(raw_dptest1,
                   dptest2_char,
                   dptest2_char_updated,
                   offset,
                   true);

    // All the values we copied out of the raw packet have to match the values
    // we originally set them to
    MUST_BE_TRUE(dptest1_int    == dptest1.getSdfInt());
    MUST_BE_TRUE(dptest1_double == dptest1.getSdfDouble());
    MUST_BE_TRUE(dptest2_float1 == dptest2p->getSdfFloat1());
    MUST_BE_TRUE(dptest2_float2 == dptest2p->getSdfFloat2());
    MUST_BE_TRUE(dptest2_char   == dptest2p->getSdfChar());

    // Read the updated raw data and compare against the updated values
    dptest1.readRaw(raw_dptest1, byteorder_opposite);

    // All the values we wrote into the raw packet have to match the values we
    // retrieved after reading the raw packet
    MUST_BE_TRUE(dptest1_int_updated    == dptest1.getSdfInt());
    MUST_BE_TRUE(dptest1_double_updated == dptest1.getSdfDouble());
    MUST_BE_TRUE(dptest2_float1_updated == dptest2p->getSdfFloat1());
    MUST_BE_TRUE(dptest2_float2_updated == dptest2p->getSdfFloat2());
    MUST_BE_TRUE(dptest2_char_updated   == dptest2p->getSdfChar());

    delete [] raw_dptest1;

    return Test::PASSED;
}
*/

//==============================================================================
void initializeDp(DataPacket_test1& dp)
{
    dp.setSdfInt(3);
    dp.setSdfDouble(4.0);

    DataPacket_test2* dp2p = dp.getNestedPacket();
    dp2p->setSdfFloat1(1.0f);
    dp2p->setSdfFloat2(2.0f);
    dp2p->setSdfChar('A');
}
