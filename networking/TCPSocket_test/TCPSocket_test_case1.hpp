#ifndef TCP_SOCKET_TEST_CASE1_HPP
#define TCP_SOCKET_TEST_CASE1_HPP

#include "Test.hpp"

class TCPSocket_test_case1 : public Test
{
public:

    // Neither of these do anything
    TCPSocket_test_case1();
    ~TCPSocket_test_case1();

    // Implements the test
    virtual Test::Result run();
};

#endif
