#if !defined TEST_CASES_HPP
#define TEST_CASES_HPP

#include <vector>

#include "Test.hpp"

class TestCases : public Test
{
public:

    TestCases();

    virtual ~TestCases();

    // Runs all added test cases
    virtual Test::Result run();

protected:

    // Derived classes should implement this to add their desired test cases
    // using addTestCase()
    virtual void addTestCases() = 0;

    // Adds a test case to the end of the list of test cases that will be run
    // when run() is called
    void addTestCase(Test* test);

private:

    std::vector<Test*> test_cases;
};

inline void TestCases::addTestCase(Test* test)
{
    test_cases.push_back(test);
}

#endif
