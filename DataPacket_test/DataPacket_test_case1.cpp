#include <iostream>

#include "DataPacket.hpp"
#include "DataPacket_test1.hpp"
#include "DataPacket_test2.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_HEADER(DataPacket_test_case1);
TEST_CONSTRUCTOR_DESTRUCTOR(DataPacket_test_case1);

//==============================================================================
Test::Result DataPacket_test_case1::body()
{
    // Initialize with some dummy data; will check for proper byteswappng later
    DataPacket_test2 dptest2(1.0f, 2.0f, 'A');
    DataPacket_test1 dptest1(3, 4.0, dptest2);

    // dptest2 data is copied to here; dptest2 is not referenced again
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

    // Byte alignment of 3 isn't used much but makes a good test.  There should
    // immediately be 2 bytes of padding after the first field,
    dptest1.setByteAlignment(3);
    dptest2p->setByteAlignment(3);
    std::cout << "Packet length (3-byte align): " << dptest1.getLengthBytes()
              << "\n";
    MUST_BE_TRUE(
        dptest1.getLengthBytes() ==
        sizeof(int) + sizeof(double) + (2 * sizeof(float)) + sizeof(char) + 9);

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

    return Test::PASSED;
}
