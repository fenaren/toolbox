#ifndef MISC_NETWORKING_TEST_HPP
#define MISC_NETWORKING_TEST_HPP

#include "TestCases.hpp"

#include "miscNetworkingTest_case1.hpp"
#include "miscNetworkingTest_case2.hpp"

class miscNetworkingTest : public TestCases
{
public:

    miscNetworkingTest();
    ~miscNetworkingTest();

    // Implements the test
    virtual void addTestCases();

private:

    miscNetworkingTest_case1 case1;
    miscNetworkingTest_case2 case2;
};

#endif
