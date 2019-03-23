#if !defined TEST_CASES_HPP
#define TEST_CASES_HPP

#include <list>
#include <string>

#include "Test.hpp"

class TestCases : public Test
{
public:

    // Sets the name
    TestCases(const std::string& name);

    // Deletes all the added test cases
    virtual ~TestCases();

    // Adds all test cases by calling addTestCases(), then runs them all in the
    // order they were added
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
