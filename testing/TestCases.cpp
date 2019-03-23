#include <iostream>
#include <list>
#include <stdexcept>
#include <string>

#include "Test.hpp"
#include "TestCases.hpp"

//==============================================================================
TestCases::TestCases(const std::string& name) :
    Test(name)
{
}

//==============================================================================
TestCases::~TestCases()
{
    for (std::list<Test*>::iterator i = test_cases.begin();
         i != test_cases.end();
         ++i)
    {
        delete *i;
    }
}

//==============================================================================
Test::Result TestCases::body()
{
    // Derived classes implement this pure virtual function to have their test
    // cases added here
    addTestCases();

    // Something is wrong if there are no test cases after we tried to add them
    if (test_cases.size() == 0)
    {
        throw std::runtime_error(
            "No test cases to run, this test is probably misconfigured");
    }

    // Run all test cases, collecting information on their results as we go
    bool any_failed = false;
    bool any_passed = false;
    for (std::list<Test*>::iterator i = test_cases.begin();
         i != test_cases.end();
         ++i)
    {
        // Run the test case
        Test::Result result = (*i)->run();

        if (result == Test::FAILED)
        {
            any_failed = true;
        }
        else if (result == Test::PASSED)
        {
            any_passed = true;
        }
    }

    // This defines how test case results are evaluated to determine how the
    // overall test went.  This assumes the three possible test results are
    // PASSED, FAILED, and SKIPPED.
    if (any_failed)
    {
        return Test::FAILED;
    }
    else if (any_passed)
    {
        return Test::PASSED;
    }

    return Test::SKIPPED;
}
