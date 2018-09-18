#ifndef TCP_SOCKET_TEST_CASE1_HPP
#define TCP_SOCKET_TEST_CASE1_HPP

#include "Test.hpp"

class TCPSocket_test_case1 : public Test
{
public:

    TCPSocket_test_case1();
    ~TCPSocket_test_case1();

    // Implements the test
    virtual Test::Result run();
};

#endif
