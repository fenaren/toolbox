#include <csignal>
#include <iostream>

#include "Program_test_tc1.hpp"

//==============================================================================
Program_test_tc1::Program_test_tc1(int argc, char** argv) :
    Program(argc, argv),
    signal_handled(false)
{
}

//==============================================================================
Program_test_tc1::~Program_test_tc1()
{
}

//==============================================================================
int Program_test_tc1::run()
{
    processDeliveredSignals();

    if (signal_handled)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

//==============================================================================
void Program_test_tc1::processDeliveredSignals()
{
    if (isSignalDelivered(SIGINT))
    {
        signal_handled = true;
    }

    unsignalAll();
}
