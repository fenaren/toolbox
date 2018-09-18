#if !defined PROGRAM_TEST_TC1_HPP
#define PROGRAM_TEST_TC1_HPP

#include "Program.hpp"

class Program_test_tc1 : public Program
{
public:

    Program_test_tc1(int argc, char** argv);
    virtual ~Program_test_tc1();

    virtual int run();

protected:

    virtual void processDeliveredSignals();

private:

    bool signal_handled;
};

#endif
