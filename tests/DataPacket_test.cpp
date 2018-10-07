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

    // The right side of the equality operator represents the known sum total of
    // all the sizes in the packet.  There are five total "leaf" fields of types
    // int, double, and float (3 of these).  The total packet length should
    // equal the sum of these when byte alignment is set to 1 byte..
    dptest1.setByteAlignment(1);
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
    std::cout << "Packet length (2-byte align): " << dptest1.getLengthBytes()
              << "\n";
    MUST_BE_TRUE(
        dptest1.getLengthBytes() ==
        sizeof(int) + sizeof(double) + (2 * sizeof(float)) + sizeof(char) + 1);

    // For a byte alignment of four things are mostly the same as a byte
    // alignment of two, but the nested packet needs 3 bytes of padding
    // afterwards
    dptest1.setByteAlignment(4);
    std::cout << "Packet length (4-byte align): " << dptest1.getLengthBytes()
              << "\n";
    MUST_BE_TRUE(
        dptest1.getLengthBytes() ==
        sizeof(int) + sizeof(double) + (2 * sizeof(float)) + sizeof(char) + 3);

    // Write out dptest1 with a 4-byte alignment and make sure it looks alright
    unsigned char* raw_dptest1 = new unsigned char(dptest1.getLengthBytes());
    dptest1.writeRaw(raw_dptest1);

    

    delete raw_dptest1;

    return Test::PASSED;
}
