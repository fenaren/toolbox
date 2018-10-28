#if !defined TEST_MACROS

#include "TestProgram.hpp"

// Using this macro makes writing TestProgram tests which compile into
// executables easier.  These kind of tests pretty much all share the same
// main() definition and signal handling setup.  This macro writes all that
// code.  This definition isn't in the TestProgram header because there's at
// least one TestProgram use case that cannot use this macro.

extern "C" void handle_signal(int sig);

#define TEST_PROGRAM_MAIN(TestClass)                \
    int main(int argc, char** argv)                 \
    {                                               \
        TestClass test;                             \
        TestProgram testprogram(argc, argv, &test); \
        return testprogram.run();                   \
    }

// MUST_BE_TRUE and MUST_BE_FALSE are intended to be used within the Test::run()
// method and work to immediately fail tests if their given expressions don't
// evaluate to boolean true and false, respectively.

// SKIP_IF_TRUE and SKIP_IF_FALSE work the same as MUST_BE_TRUE and
// MUST_BE_FALSE except they immediately skip the test instead of immediately
// failing it.

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

#define SKIP_IF_TRUE(expression) \
    if (expression)              \
    {                            \
        return Test::SKIPPED;    \
    }

#define SKIP_IF_FALSE(expression) \
    if (!(expression))            \
    {                             \
        return Test::SKIPPED;     \
    }

#endif
