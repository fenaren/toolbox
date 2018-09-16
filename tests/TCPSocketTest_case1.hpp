#ifndef TCP_SOCKET_TEST_CASE1_HPP
#define TCP_SOCKET_TEST_CASE1_HPP

#include "Test.hpp"

class TCPSocketTest_case1 : public Test
{
public:

    TCPSocketTest_case1();
    ~TCPSocketTest_case1();

    // Implements the test
    virtual Test::Result run();
};

#endif
