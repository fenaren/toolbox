#ifndef MISC_NETWORKING_TEST_CASE3_HPP
#define MISC_NETWORKING_TEST_CASE3_HPP

#include "Test.hpp"

class miscNetworking_test_case3 : public Test
{
public:

    // Neither of these do anything
    miscNetworking_test_case3();
    ~miscNetworking_test_case3();

    // Implements the test
    virtual Test::Result run();
};

#endif
