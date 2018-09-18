#ifndef TCP_SOCKET_TEST_CASE2_HPP
#define TCP_SOCKET_TEST_CASE2_HPP

#include "Test.hpp"

class TCPSocket_test_case2 : public Test
{
public:

    // Neither of these do anything
    TCPSocket_test_case2();
    ~TCPSocket_test_case2();

    // Implements the test
    virtual Test::Result run();
};

#endif
