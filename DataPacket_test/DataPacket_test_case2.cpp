#include <cstdint>
#include <cstring>
#include <iostream>

#include "DataPacket.hpp"
#include "DataPacket_test1.hpp"
#include "DataPacket_test2.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"
#include "pullUpdatePush.hpp"

TEST_HEADER(DataPacket_test_case2);
TEST_CONSTRUCTOR_DESTRUCTOR(DataPacket_test_case2);

//==============================================================================
Test::Result DataPacket_test_case2::body()
{
    // Initialize with some dummy data; will check for proper byteswappng later
    DataPacket_test2 dptest2(1.0f, 2.0f, 'A');
    DataPacket_test1 dptest1(3, 4.0, dptest2);

    // dptest2 data is copied to here; dptest2 is not referenced again
    DataPacket_test2* dptest2p = dptest1.getNestedPacket();

    dptest1.setAlignment(3, DataPacket::BYTES);
    dptest2p->setAlignment(3, DataPacket::BYTES);

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
