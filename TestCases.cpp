#include <iostream>
#include <iterator>
#include <vector>

#include "Test.hpp"
#include "TestCases.hpp"

//==============================================================================
TestCases::TestCases()
{
}

//==============================================================================
TestCases::~TestCases()
{
}

//==============================================================================
Test::Result TestCases::run()
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
        Test::Result result = (*i)->run();

        std::cout << "Test case "
                  << std::distance(test_cases.begin(), i) + 1 << " ";

        if (result == Test::FAILED)
        {
            any_failed = true;
            std::cout << "failed";
        }
        else if (result == Test::PASSED)
        {
            any_passed = true;
            std::cout << "passed";
        }
        else if (result == Test::SKIPPED)
        {
            std::cout << "skipped";
        }

        std::cout << "\n";
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
