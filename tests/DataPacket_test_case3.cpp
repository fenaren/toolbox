#include <cstring>
#include <iostream>

#include "DataPacket_test_case3.hpp"

#include "DataPacket.hpp"
#include "DataPacket_test1.hpp"
#include "DataPacket_test2.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

//==============================================================================
DataPacket_test_case3::DataPacket_test_case3()
{
}

//==============================================================================
DataPacket_test_case3::~DataPacket_test_case3()
{
}

//==============================================================================
Test::Result DataPacket_test_case3::run()
{
    // Initialize with some dummy data; will check for proper byteswappng later
    DataPacket_test2 dptest2(1.0f, 2.0f, 'A');
    DataPacket_test1 dptest1(3, 4.0, dptest2);

    // dptest2 data is copied to here; dptest2 is not referenced again
    DataPacket_test2* dptest2p = dptest1.getNestedPacket();

    dptest1.setByteAlignment(3);
    dptest2p->setByteAlignment(3);

    // Write out dptest1 with a 3-byte alignment and make sure it looks alright
    unsigned char* raw_dptest1 = new unsigned char[dptest1.getLengthBytes()];
    dptest1.writeRaw(raw_dptest1);

    unsigned int offset = 0;

    // Grab sdf_int; it should be at the very beginning of the raw packet
    int dptest1_int;
    memcpy(&dptest1_int, raw_dptest1, sizeof(int));
    // Push an updated int into its place to read later
    int dptest1_int_updated = dptest1_int + 1;
    memcpy(raw_dptest1 + offset, &dptest1_int_updated, sizeof(int));
    offset += sizeof(int);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab sdf_double; it should be right after sdf_int, which means an offset
    // of sizeof(int)
    double dptest1_double;
    memcpy(&dptest1_double, raw_dptest1 + offset, sizeof(double));
    // Push an updated double into its place to read later
    double dptest1_double_updated = dptest1_double + 1;
    memcpy(raw_dptest1 + offset, &dptest1_double_updated, sizeof(double));
    offset += sizeof(double);

    // Should be 1 byte of padding here
    offset += 1;

    // Grab sdf_float1 from the nested packet; it should be right after all the
    // fields in the top-level packet, since we're still aligned on 4 bytes
    float dptest2_float1;
    memcpy(&dptest2_float1, raw_dptest1 + offset, sizeof(float));
    // Push an updated float into its place to read later
    float dptest2_float1_updated = dptest2_float1 + 1;
    memcpy(raw_dptest1 + offset, &dptest2_float1_updated, sizeof(float));
    offset += sizeof(float);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab sdf_float2 from the nested packet; still aligned on 4 bytes so it's
    // still immediately after the last thing
    float dptest2_float2;
    memcpy(&dptest2_float2, raw_dptest1 + offset, sizeof(float));
    // Push an updated float into its place to read later
    float dptest2_float2_updated = dptest2_float2 + 1;
    memcpy(raw_dptest1 + offset, &dptest2_float2_updated, sizeof(float));

    offset += sizeof(float);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab sdf_char from the nested packet; still aligned on 4 bytes so it's
    // still immediately after the last thing
    char dptest2_char;
    memcpy(&dptest2_char, raw_dptest1 + offset, sizeof(char));
    // Push an updated char into its place to read later
    char dptest2_char_updated = dptest2_char + 1;
    memcpy(raw_dptest1 + offset, &dptest2_char_updated, sizeof(char));
    offset += sizeof(char);

    // Should be 2 bytes of padding here
    offset += 2;

    MUST_BE_TRUE(dptest1_int    == dptest1.getSdfInt());
    MUST_BE_TRUE(dptest1_double == dptest1.getSdfDouble());
    MUST_BE_TRUE(dptest2_float1 == dptest1.getNestedPacket()->getSdfFloat1());
    MUST_BE_TRUE(dptest2_float2 == dptest1.getNestedPacket()->getSdfFloat2());
    MUST_BE_TRUE(dptest2_char   == dptest1.getNestedPacket()->getSdfChar());

    // Read the updated raw data and compare against the updated values
    dptest1.readRaw(raw_dptest1);

    MUST_BE_TRUE(dptest1_int_updated    == dptest1.getSdfInt());
    MUST_BE_TRUE(dptest1_double_updated == dptest1.getSdfDouble());
    MUST_BE_TRUE(
        dptest2_float1_updated == dptest1.getNestedPacket()->getSdfFloat1());
    MUST_BE_TRUE(
        dptest2_float2_updated == dptest1.getNestedPacket()->getSdfFloat2());
    MUST_BE_TRUE(
        dptest2_char_updated   == dptest1.getNestedPacket()->getSdfChar());

    delete [] raw_dptest1;

    return Test::PASSED;
}
