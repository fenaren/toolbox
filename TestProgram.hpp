#if !defined TEST_PROGRAM_HPP
#define TEST_PROGRAM_HPP

#include "Program.hpp"

class Test;

class TestProgram : public Program
{
public:

    TestProgram(int argc, char** argv, Test* test);

    ~TestProgram();

    // Runs the provided test and maps the result to return codes
    virtual int run();

private:

    Test* test;
};

#endif
