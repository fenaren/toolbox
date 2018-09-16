#ifndef IPV4_ADDRESS_TEST_HPP
#define IPV4_ADDRESS_TEST_HPP

#include "Test.hpp"

class Ipv4AddressTest : public Test
{
public:

    Ipv4AddressTest();
    ~Ipv4AddressTest();

    // Implements the test
    virtual Test::Result run();
};

#endif
