#include <iostream>
#include <string.h>

#include "UDPSocket.hpp"

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_PROGRAM_BEGIN(UDPSocket_test)
TEST(SendReceive_TwoSockets)
TEST_CASES_PROGRAM_END(UDPSocket_test)

//==============================================================================
void UDPSocket_test::addTestCases()
{
    addTestCase(new SendReceive_TwoSockets());
}

//==============================================================================
Test::Result UDPSocket_test::SendReceive_TwoSockets::body()
{
    unsigned int port1 = 0;  // Use whatever port is available
    unsigned int port2 = 0;  // Use whatever port is available

    unsigned char send1[]      = {'o',  'n',  'e',  '\0'};
    unsigned char send1_recv[] = {'\0', '\0', '\0', '\0'};
    unsigned char send2[]      = {'t',  'w',  'o',  '\0'};
    unsigned char send2_recv[] = {'\0', '\0', '\0', '\0'};
    int send_size = 4;  // Must equal the length of all four arrays

    UDPSocket socket1;
    UDPSocket socket2;

    MUST_BE_TRUE(socket1.bind(port1));
    MUST_BE_TRUE(socket2.bind(port2));

    std::cout << "Socket1 using port " << port1 << "\n";
    std::cout << "Socket2 using port " << port2 << "\n";

    // As long as this goes out to localhost it should be almost instantaneous,
    // at least in human terms
    MUST_BE_TRUE(socket1.sendTo("localhost", port2));
    MUST_BE_TRUE(socket2.sendTo("localhost", port1));

    // Send something one way
    MUST_BE_TRUE(socket1.write(send1, send_size) == send_size);
    MUST_BE_TRUE(socket2.read(send1_recv, send_size) == send_size);

    // Check that we got exactly what we sent
    std::cout << "Sent " << send1 << " received " << send1_recv << "\n";
    MUST_BE_TRUE(memcmp(send1, send1_recv, send_size) == 0);

    // Send something back
    MUST_BE_TRUE(socket2.write(send2, send_size) == send_size);
    MUST_BE_TRUE(socket1.read(send2_recv, send_size) == send_size);

    // Check that we got exactly what we sent
    std::cout << "Sent " << send2 << " received " << send2_recv << "\n";
    MUST_BE_TRUE(memcmp(send2, send2_recv, send_size) == 0)

    return Test::PASSED;
}
