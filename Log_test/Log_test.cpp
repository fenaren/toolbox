#include <iostream>

#include "Log.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TRIVIAL_TEST(Log_test);

//==============================================================================
Test::Result Log_test::body()
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
