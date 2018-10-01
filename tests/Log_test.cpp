#include <iostream>

#include "Log_test.hpp"

#include "Log.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(Log_test);

//==============================================================================
Log_test::Log_test()
{
}

//==============================================================================
Log_test::~Log_test()
{
}

//==============================================================================
Test::Result Log_test::run()
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
