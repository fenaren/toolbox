#ifndef MISC_TEST_CASE1_HPP
#define MISC_TEST_CASE1_HPP

#include "Test.hpp"

class misc_test_case1 : public Test
{
public:

    // Neither of these do anything
    misc_test_case1();
    ~misc_test_case1();

    // Implements the test
    virtual Test::Result run();
};

#endif
