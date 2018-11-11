#if !defined TEST_CASES_HPP
#define TEST_CASES_HPP

#include <vector>

#include "Test.hpp"

class TestCases : public Test
{
public:

    // Does nothing
    TestCases();

    // Deletes all the added test cases
    virtual ~TestCases();

    // Adds all test cases by calling addTestCases(), then runs them all
    virtual Test::Result run();

protected:

    // Adds a test case to the end of the list of test cases that will be run
    // when run() is called
    void addTestCase(Test* test);

    // Derived classes must implement this to add their desired test cases using
    // addTestCase()
    virtual void addTestCases() = 0;

private:

    std::vector<Test*> test_cases;
};

inline void TestCases::addTestCase(Test* test)
{
    test_cases.push_back(test);
}

#endif
