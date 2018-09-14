#if !defined TEST_CASES_HPP
#define TEST_CASES_HPP

#include <vector>

#include "Test.hpp"

class TestCases : public Test
{
public:

    TestCases();

    virtual ~TestCases();

    // Derived classes should override this to implement the desired test
    virtual int run();

protected:

    void addTest(Test* test);

private:

    std::vector<Test*> test_cases;
};

inline void TestCases::addTest(Test* test)
{
    test_cases.push_back(test);
}

#endif
