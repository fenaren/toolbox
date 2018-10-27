#if !defined TEST_PROGRAM_HPP
#define TEST_PROGRAM_HPP

#include "Program.hpp"

class Test;

class TestProgram : public Program
{
public:

    // Constructs base class, initializes "test" class member
    TestProgram(int argc, char** argv, Test* test);

    // Does nothing
    ~TestProgram();

    // Runs the provided test and maps the result to return codes
    virtual int run();

protected:

    // By default Do nothing in response to signals.  Individual tests can
    // override this if they want
    virtual void processDeliveredSignals();

private:

    Test* test;
};

#endif
