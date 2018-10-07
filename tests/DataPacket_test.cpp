#include <iostream>

#include "DataPacket_test.hpp"

#include "DataPacket.hpp"
#include "DataPacket_test1.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(DataPacket_test);

//==============================================================================
DataPacket_test::DataPacket_test()
{
}

//==============================================================================
DataPacket_test::~DataPacket_test()
{
}

//==============================================================================
Test::Result DataPacket_test::run()
{
    // Initialize with some dummy data; will check for proper byteswappng later
    DataPacket_test2 dptest2(1.0f, 2.0f, 'A');
    DataPacket_test1 dptest1(3, 4.0, dptest2);

    // dptest2 data is copied to here
    DataPacket_test2* dptest2p = dptest1.getNestedPacket();

    // The right side of the equality operator represents the known sum total of
    // all the sizes in the packet.  There are five total "leaf" fields of types
    // int, double, and float (3 of these).  The total packet length should
    // equal the sum of these when byte alignment is set to 1 byte..
    dptest1.setByteAlignment(1);
    dptest2p->setByteAlignment(1);
    std::cout << "Packet length (1-byte align): " << dptest1.getLengthBytes()
              << "\n";
    MUST_BE_TRUE(
        dptest1.getLengthBytes() ==
        sizeof(int) + sizeof(double) + (2 * sizeof(float)) + sizeof(char));

    // For a byte alignment of two the total packet size will be different.  The
    // types are the same but some fields should have padding afterwards which
    // will increase the total packet length.  The top-level packet is already
    // aligned on 2 bytes, but the nested packet isn't and should include a byte
    // of padding at the end.
    dptest1.setByteAlignment(2);
    dptest2p->setByteAlignment(2);
    std::cout << "Packet length (2-byte align): " << dptest1.getLengthBytes()
              << "\n";
    MUST_BE_TRUE(
        dptest1.getLengthBytes() ==
        sizeof(int) + sizeof(double) + (2 * sizeof(float)) + sizeof(char) + 1);

    // For a byte alignment of four things are mostly the same as a byte
    // alignment of two, but the nested packet needs 3 bytes of padding
    // afterwards
    dptest1.setByteAlignment(4);
    dptest2p->setByteAlignment(4);
    std::cout << "Packet length (4-byte align): " << dptest1.getLengthBytes()
              << "\n";
    MUST_BE_TRUE(
        dptest1.getLengthBytes() ==
        sizeof(int) + sizeof(double) + (2 * sizeof(float)) + sizeof(char) + 3);

    // Byte alignment of 3 isn't used much but makes a good test.  There should
    // immediately be 2 bytes of padding after the first field,
    dptest1.setByteAlignment(3);
    dptest2p->setByteAlignment(3);
    std::cout << "Packet length (3-byte align): " << dptest1.getLengthBytes()
              << "\n";
    MUST_BE_TRUE(
        dptest1.getLengthBytes() ==
        sizeof(int) + sizeof(double) + (2 * sizeof(float)) + sizeof(char) + 9);

    // Write out dptest1 with a 4-byte alignment and make sure it looks alright
    unsigned char* raw_dptest1 = new unsigned char[dptest1.getLengthBytes()];
    dptest1.writeRaw(raw_dptest1);

    unsigned int offset = 0;

    // Grab sdf_int; it should be at the very beginning of the raw packet
    int dptest1_int;
    memcpy(&dptest1_int, raw_dptest1, sizeof(int));
    offset += sizeof(int);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab sdf_double; it should be right after sdf_int, which means an offset
    // of sizeof(int)
    double dptest1_double;
    memcpy(&dptest1_double, raw_dptest1 + offset, sizeof(double));
    offset += sizeof(double);

    // Should be 1 byte of padding here
    offset += 1;

    // Grab sdf_float1 from the nested packet; it should be right after all the
    // fields in the top-level packet, since we're still aligned on 4 bytes
    float dptest2_float1;
    memcpy(&dptest2_float1, raw_dptest1 + offset, sizeof(float));
    offset += sizeof(float);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab sdf_float2 from the nested packet; still aligned on 4 bytes so it's
    // still immediately after the last thing
    float dptest2_float2;
    memcpy(&dptest2_float2, raw_dptest1 + offset, sizeof(float));
    offset += sizeof(float);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab sdf_char from the nested packet; still aligned on 4 bytes so it's
    // still immediately after the last thing
    char dptest2_char;
    memcpy(&dptest2_char, raw_dptest1 + offset, sizeof(char));
    offset += sizeof(char);

    // Should be 2 bytes of padding here
    offset += 2;

    MUST_BE_TRUE(dptest1_int    == dptest1.getSdfInt());
    MUST_BE_TRUE(dptest1_double == dptest1.getSdfDouble());
    MUST_BE_TRUE(dptest2_float1 == dptest1.getNestedPacket()->getSdfFloat1());
    MUST_BE_TRUE(dptest2_float2 == dptest1.getNestedPacket()->getSdfFloat2());
    MUST_BE_TRUE(dptest2_char   == dptest1.getNestedPacket()->getSdfChar());

    delete [] raw_dptest1;

    return Test::PASSED;
}
