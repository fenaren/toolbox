#include <iostream>

#include "Log_test.hpp"

#include "Log.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(Log_test);

//==============================================================================
void Log_test::addTestCases()
{
    ADD_TEST_CASE(WriteWarningError);
}

//==============================================================================
Test::Result Log_test::WriteWarningError::body()
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
