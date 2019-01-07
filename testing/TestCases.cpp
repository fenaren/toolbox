#include <iostream>
#include <string>
#include <vector>

#include "Test.hpp"
#include "TestCases.hpp"

//==============================================================================
TestCases::TestCases(const std::string& name) :
    Test(name)
{
}

//==============================================================================
// Delete all the added test cases
//==============================================================================
TestCases::~TestCases()
{
    for (std::vector<Test*>::iterator i = test_cases.begin();
         i != test_cases.end();
         ++i)
    {
        delete *i;
    }
}

//==============================================================================
// Adds all test cases by calling addTestCases(), then runs them all in the
// order they were added
//==============================================================================
Test::Result TestCases::body()
{
    // Derived classes implement this pure virtual function to have their test
    // cases added here
    addTestCases();

    // Run all test cases, collecting information on their results as we go
    bool any_failed = false;
    bool any_passed = false;
    for (std::vector<Test*>::iterator i = test_cases.begin();
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
