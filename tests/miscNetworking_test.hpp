#ifndef MISC_NETWORKING_TEST_HPP
#define MISC_NETWORKING_TEST_HPP

#include "TestCases.hpp"

#include "miscNetworking_test_case1.hpp"
#include "miscNetworking_test_case2.hpp"

class miscNetworking_test : public TestCases
{
public:

    miscNetworking_test();
    ~miscNetworking_test();

    // Implements the test
    virtual void addTestCases();

private:

    miscNetworking_test_case1 case1;
    miscNetworking_test_case2 case2;
};

#endif
