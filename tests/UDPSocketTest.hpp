#ifndef UDP_SOCKET_TEST_HPP
#define UDP_SOCKET_TEST_HPP

#include "Test.hpp"

class UDPSocketTest : public Test
{
public:

    UDPSocketTest();
    ~UDPSocketTest();

    // Implements the test
    virtual Test::Result run();
};

#endif
