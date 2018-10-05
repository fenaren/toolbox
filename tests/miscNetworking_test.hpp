#ifndef MISC_NETWORKING_TEST_HPP
#define MISC_NETWORKING_TEST_HPP

#include "TestCases.hpp"

#include "miscNetworking_test_case1.hpp"
#include "miscNetworking_test_case2.hpp"
#include "miscNetworking_test_case3.hpp"

class miscNetworking_test : public TestCases
{
public:

    // Neither of these do anything
    miscNetworking_test();
    ~miscNetworking_test();

    // Implements the test
    virtual void addTestCases();

private:

    miscNetworking_test_case1 case1;
    miscNetworking_test_case2 case2;
    miscNetworking_test_case3 case3;
};

#endif
