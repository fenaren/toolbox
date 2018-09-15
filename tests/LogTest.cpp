#include <iostream>

#include "LogTest.hpp"

#include "Log.hpp"
#include "Test.hpp"
#include "TestProgram.hpp"

//==============================================================================
LogTest::LogTest()
{
}

//==============================================================================
LogTest::~LogTest()
{
}

//==============================================================================
Test::Result LogTest::run()
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
    LogTest test;
    TestProgram testprogram(argc, argv, &test);
    return testprogram.run();
}
