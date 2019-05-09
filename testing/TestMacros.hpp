#if !defined TEST_MACROS

#include <iostream>
#include <string>

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestProgram.hpp"

// Using these macros makes writing TestProgram tests which compile into
// executables easier.  These macros save lots of duplicate code, but more
// importantly they make writing tests easier for the developer.  It's easy to
// think "how hard could it be to write this stuff out oneself", but developers
// can be reluctant to write tests in the first place, and anything we can do to
// make the test-writing process easier is extremely valuable.

#define TEST(TestClass)                                                  \
    class TestClass : public Test                                        \
    {                                                                    \
    public:                                                              \
        TestClass(const std::string& name = #TestClass) : Test(name) {}; \
        ~TestClass() {};                                                 \
    protected:                                                           \
        virtual Test::Result body();                                     \
    };

#define TEST_CASES_BEGIN(TestClass)                                           \
    class TestClass : public TestCases                                        \
    {                                                                         \
    public:                                                                   \
        TestClass(const std::string& name = #TestClass) : TestCases(name) {}; \
        ~TestClass() {};                                                      \
        virtual void addTestCases();

#define TEST_CASES_END(TestClass) };

#define TEST_PROGRAM_MAIN(TestClass)                \
    int main(int argc, char** argv)                 \
    {                                               \
        TestClass test;                             \
        TestProgram testprogram(argc, argv, &test); \
        return testprogram.run();                   \
    }

#define ADD_TEST_CASE(TestCase) addTestCase(new TestCase())

// MUST_BE_TRUE and MUST_BE_FALSE are intended to be used within the Test::run()
// method and work to immediately fail tests if their given expressions don't
// evaluate to boolean true and false, respectively.

// SKIP_IF_TRUE and SKIP_IF_FALSE work the same as MUST_BE_TRUE and
// MUST_BE_FALSE except they immediately skip the test instead of immediately
// failing it.

#define MUST_BE_TRUE(expression)                                      \
    if (!(expression))                                                \
    {                                                                 \
        std::cout << "MUST_BE_TRUE failing on \"" #expression "\"\n"; \
        return Test::FAILED;                                          \
    }

#define MUST_BE_FALSE(expression)                                      \
    if (expression)                                                    \
    {                                                                  \
        std::cout << "MUST_BE_FALSE failing on \"" #expression "\"\n"; \
        return Test::FAILED;                                           \
    }

#define SKIP_IF_TRUE(expression)                                       \
    if (expression)                                                    \
    {                                                                  \
        std::cout << "SKIP_IF_TRUE skipping on \"" #expression "\"\n"; \
        return Test::SKIPPED;                                          \
    }

#define SKIP_IF_FALSE(expression)                                       \
    if (!(expression))                                                  \
    {                                                                   \
        std::cout << "SKIP_IF_FALSE skipping on \"" #expression "\"\n"; \
        return Test::SKIPPED;                                           \
    }

#endif
