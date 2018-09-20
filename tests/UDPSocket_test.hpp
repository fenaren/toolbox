#ifndef UDP_SOCKET_TEST_HPP
#define UDP_SOCKET_TEST_HPP

#include "Test.hpp"

class UDPSocket_test : public Test
{
public:

    // Neither of these do anything
    UDPSocket_test();
    ~UDPSocket_test();

    // Implements the test
    virtual Test::Result run();
};

#endif
