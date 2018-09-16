#if !defined TEST_PROGRAM_MAIN

#include "TestProgram.hpp"

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
