#ifndef NETWORK_ADDRESS_TEST_HPP
#define NETWORK_ADDRESS_TEST_HPP

#include "Test.hpp"

class NetworkAddress_test : public Test
{
public:

    // Neither of these do anything
    NetworkAddress_test();
    ~NetworkAddress_test();

    // Implements the test
    virtual Test::Result run();
};

#endif
