#ifndef RAW_SOCKET_TEST_HPP
#define RAW_SOCKET_TEST_HPP

#include "Test.hpp"

class RawSocket_test : public Test
{
public:

    RawSocket_test();
    ~RawSocket_test();

    // Implements the test
    virtual Test::Result run();
};

#endif
