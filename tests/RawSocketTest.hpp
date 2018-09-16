#ifndef RAW_SOCKET_TEST_HPP
#define RAW_SOCKET_TEST_HPP

#include "Test.hpp"

class RawSocketTest : public Test
{
public:

    RawSocketTest();
    ~RawSocketTest();

    // Implements the test
    virtual Test::Result run();
};

#endif
