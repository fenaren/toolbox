#if !defined TEST_CASES_HPP
#define TEST_CASES_HPP

#include <list>
#include <string>

#include "Test.hpp"

// This class allows sets of related Tests to be grouped and executed together.
// It does this by storing an internal list of Tests and then implementing the
// Test::body() pure virtual member function in such a way that when a TestCases
// (which is itself a Test) is run, all tests in its internal list are run and
// the result of all those tests is aggregated into a single result and
// returned.  See documentation for the TestCases::body() function for a
// description of how test case results are aggregated.
class TestCases : public Test
{
public:

    // Sets the name
    TestCases(const std::string& name);

    // Deletes all the added test cases
    virtual ~TestCases();

    // Adds all test cases by calling addTestCases(), then runs them all in the
    // order they were added.  Test::FAILED is returned if any test cases fail
    // (return Test::FAILED).  If no test cases fail and at least one test case
    // passed (returned Test::PASSED), Test::PASSED is returned.  If no test
    // cases pass or fail, Test::SKIPPED is returned.
    virtual Test::Result body();

protected:

    // Adds a test case to the end of the list of test cases that will be run
    // when run() is called
    void addTestCase(Test* test);

    // Derived classes must implement this to add their desired test cases using
    // addTestCase()
    virtual void addTestCases() = 0;

private:

    std::list<Test*> test_cases;
};

//==============================================================================
inline void TestCases::addTestCase(Test* test)
{
    test_cases.push_back(test);
}

#endif
