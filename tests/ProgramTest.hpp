#ifndef PROGRAM_TEST_HPP
#define PROGRAM_TEST_HPP

#include "Test.hpp"

class ProgramTest : public Test
{
public:

    ProgramTest();
    ~ProgramTest();

    // Implements the test
    virtual Test::Result run();
};

#endif
