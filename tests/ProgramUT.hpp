#if !defined PROGRAM_UT_HPP
#define PROGRAM_UT_HPP

#include "Program.hpp"

class ProgramUT : public Program
{
public:

    ProgramUT(int argc, char** argv);
    virtual ~ProgramUT();

    virtual int run();

protected:

    virtual void processDeliveredSignals();

private:

    bool signal_handled;
};

#endif
