#ifndef MISC_NETWORKING_TEST_CASE2_HPP
#define MISC_NETWORKING_TEST_CASE2_HPP

#include "Test.hpp"

class miscNetworking_test_case2 : public Test
{
public:

    miscNetworking_test_case2();
    ~miscNetworking_test_case2();

    // Implements the test
    virtual Test::Result run();
};

#endif
