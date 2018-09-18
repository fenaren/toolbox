#ifndef MISC_NETWORKING_TEST_CASE1_HPP
#define MISC_NETWORKING_TEST_CASE1_HPP

#include "Test.hpp"

class miscNetworking_test_case1 : public Test
{
public:

    // Neither of these do anything
    miscNetworking_test_case1();
    ~miscNetworking_test_case1();

    // Implements the test
    virtual Test::Result run();
};

#endif
