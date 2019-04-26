#include <iostream>

#include "Log.hpp"

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_PROGRAM_BEGIN(Log_test)
TEST(WriteWarningError)
TEST_CASES_PROGRAM_END(Log_test)

//==============================================================================
void Log_test::addTestCases()
{
    addTestCase(new WriteWarningError());
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
