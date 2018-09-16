#ifndef TCP_SOCKET_TEST_CASE2_HPP
#define TCP_SOCKET_TEST_CASE2_HPP

#include "Test.hpp"

class TCPSocketTest_case2 : public Test
{
public:

    TCPSocketTest_case2();
    ~TCPSocketTest_case2();

    // Implements the test
    virtual Test::Result run();
};

#endif
