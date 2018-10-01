#if !defined TEST_MACROS

#include "TestProgram.hpp"

// Using this macro makes writing TestProgram tests which compile into
// executables easier.  These kind of tests pretty much all share the same
// main() definition and signal handling setup.  This macro writes all that
// code.  This definition isn't in the TestProgram header because there's at
// least one TestProgram use case that cannot use this macro.

#define TEST_PROGRAM_MAIN(TestClass)                \
    TestProgram* testprogram_p = 0;                 \
                                                    \
    extern "C" void handle_signal(int sig)          \
    {                                               \
        if (testprogram_p)                          \
        {                                           \
            testprogram_p->signal(sig);             \
        }                                           \
    }                                               \
                                                    \
    int main(int argc, char** argv)                 \
    {                                               \
        TestClass test;                             \
        TestProgram testprogram(argc, argv, &test); \
        testprogram_p = &testprogram;               \
        return testprogram.run();                   \
    }

// MUST_BE_TRUE and MUST_BE_FALSE are intended to be used within the Test::run()
// method and work to immediately fail tests if their given expressions don't
// evaluate to boolean true and false, respectively.

#define MUST_BE_TRUE(expression) \
    if (!(expression))           \
    {                            \
        return Test::FAILED;     \
    }

#define MUST_BE_FALSE(expression) \
    if (expression)               \
    {                             \
        return Test::FAILED;      \
    }

#endif
