#if !defined TCP_SOCKET_TEST
#define TCP_SOCKET_TEST

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(TCPSocket_test)

    TEST(SendReceive_TwoSockets)
    TEST(SendReceive_TwoSockets_AcceptSpawn)

TEST_CASES_END(TCPSocket_test)

#endif
