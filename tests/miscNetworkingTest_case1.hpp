#ifndef MISC_NETWORKING_TEST_CASE1_HPP
#define MISC_NETWORKING_TEST_CASE1_HPP

#include "Test.hpp"

class miscNetworkingTest_case1 : public Test
{
public:

    miscNetworkingTest_case1();
    ~miscNetworkingTest_case1();

    // Implements the test
    virtual Test::Result run();
};

#endif
