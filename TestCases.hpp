#if !defined TEST_CASES_HPP
#define TEST_CASES_HPP

#include <vector>

#include "Test.hpp"

class TestCases : public Test
{
public:

    TestCases();

    virtual ~TestCases();

    virtual Test::Result run();

protected:

    virtual void addTestCases() = 0;

    void addTestCase(Test* test);

private:

    std::vector<Test*> test_cases;
};

inline void TestCases::addTestCase(Test* test)
{
    test_cases.push_back(test);
}

#endif
