#ifndef MAC_ADDRESS_TEST_HPP
#define MAC_ADDRESS_TEST_HPP

#include "Test.hpp"

class MacAddressTest : public Test
{
public:

    MacAddressTest();
    ~MacAddressTest();

    // Implements the test
    virtual Test::Result run();
};

#endif
