#ifndef MAC_ADDRESS_TEST_HPP
#define MAC_ADDRESS_TEST_HPP

#include "Test.hpp"

class MacAddress_test : public Test
{
public:

    // Neither of these do anything
    MacAddress_test();
    ~MacAddress_test();

    // Implements the test
    virtual Test::Result run();
};

#endif
