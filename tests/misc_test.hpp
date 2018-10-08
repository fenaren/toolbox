#ifndef MISC_TEST_HPP
#define MISC_TEST_HPP

#include "TestCases.hpp"

#include "misc_test_case1.hpp"

class misc_test : public TestCases
{
public:

    // Neither of these do anything
    misc_test();
    ~misc_test();

    // Implements the test
    virtual void addTestCases();

private:

    misc_test_case1 case1;
};

#endif
