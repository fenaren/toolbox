#ifndef IPV4_ADDRESS_TEST_HPP
#define IPV4_ADDRESS_TEST_HPP

#include "Test.hpp"

class Ipv4Address_test : public Test
{
public:

    Ipv4Address_test();
    ~Ipv4Address_test();

    // Implements the test
    virtual Test::Result run();
};

#endif
