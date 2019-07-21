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
    ADD_TEST_CASE(GreenwichMeanTime);
    ADD_TEST_CASE(LocalTime);
}

//==============================================================================
void Log_test::GreenwichMeanTime::addTestCases()
{
    ADD_TEST_CASE(Normal);
    ADD_TEST_CASE(Warning);
    ADD_TEST_CASE(Error);
}

//==============================================================================
void Log_test::LocalTime::addTestCases()
{
    ADD_TEST_CASE(Normal);
    ADD_TEST_CASE(Warning);
    ADD_TEST_CASE(Error);
}

//==============================================================================
Test::Result Log_test::GreenwichMeanTime::Normal::body()
{
    Log log;
    log.useGreenwichMeanTime();
    log.write("message1");

    return Test::PASSED;
}

//==============================================================================
Test::Result Log_test::GreenwichMeanTime::Warning::body()
{
    Log log;
    log.useGreenwichMeanTime();
    log.writeWarning("message1");

    return Test::PASSED;
}

//==============================================================================
Test::Result Log_test::GreenwichMeanTime::Error::body()
{
    Log log;
    log.useGreenwichMeanTime();
    log.writeError("message1");

    return Test::PASSED;
}

//==============================================================================
Test::Result Log_test::LocalTime::Normal::body()
{
    Log log;
    log.useLocalTime();
    log.write("message1");

    return Test::PASSED;
}

//==============================================================================
Test::Result Log_test::LocalTime::Warning::body()
{
    Log log;
    log.useLocalTime();
    log.writeWarning("message1");

    return Test::PASSED;
}

//==============================================================================
Test::Result Log_test::LocalTime::Error::body()
{
    Log log;
    log.useLocalTime();
    log.writeError("message1");

    return Test::PASSED;
}
