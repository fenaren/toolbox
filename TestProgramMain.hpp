#if !defined TEST_PROGRAM_MAIN

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

#endif
