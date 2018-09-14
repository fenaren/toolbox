#include <iostream>

#include "Log.hpp"
#include "LogUT.hpp"
#include "Test.hpp"

//==============================================================================
LogUT::LogUT(int argc, char** argv) :
    Program(argc, argv)
{
}

//==============================================================================
LogUT::~LogUT()
{
}

//==============================================================================
int LogUT::run()
{
    Log log;
    log.write("message1");
    log.writeWarning("message2");
    log.writeError("message3");

    log.useLocalTime();
    log.write("message1");
    log.writeWarning("message2");
    log.writeError("message3");

    return Test::PASSED;
}

//==============================================================================
int main(int argc, char** argv)
{
    LogUT log_ut(argc, argv);
    return log_ut.run();
}
