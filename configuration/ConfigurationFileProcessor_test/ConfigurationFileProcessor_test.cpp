#include <iostream>
#include <list>
#include <string>

#include "ConfigurationFileProcessor_test.hpp"

#include "ConfigurationFileProcessor.hpp"
#include "ConfigurationParameter.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(Configuration::FileProcessor_test);

//=============================================================================================
void Configuration::FileProcessor_test::addTestCases()
{
    ADD_TEST_CASE(Process);
}

//=============================================================================================
Test::Result Configuration::FileProcessor_test::Process::body()
{
    Parameter<std::list<std::string> > eth_interface;
    Parameter<std::string> log_file;
    Parameter<std::string> pid_file;
    Parameter<bool> daemonize;
    Parameter<unsigned int> device_check_period;
    Parameter<unsigned int> device_response_grace_period;
    Parameter<bool> aggressive_garp;

    FileProcessor file_processor;
    file_processor.registerParameter(&eth_interface, "ETH_INTERFACE");
    file_processor.registerParameter(&log_file, "LOG_FILE");
    file_processor.registerParameter(&pid_file, "PID_FILE");
    file_processor.registerParameter(&daemonize, "DAEMONIZE");
    file_processor.registerParameter(&device_check_period, "DEVICE_CHECK_PERIOD");
    file_processor.registerParameter(&device_response_grace_period,
                                     "DEVICE_RESPONSE_GRACE_PERIOD");
    file_processor.registerParameter(&aggressive_garp, "AGGRESSIVE_GARP");

    file_processor.process("config");

    MUST_BE_TRUE(eth_interface == std::list<std::string>({"eth0"}));
    MUST_BE_TRUE(log_file == "/var/log/sproxy.log");
    MUST_BE_TRUE(pid_file == "/var/run/sproxy.pid");
    MUST_BE_TRUE(daemonize);
    MUST_BE_TRUE(device_check_period == 10);
    MUST_BE_TRUE(device_response_grace_period == 1);
    MUST_BE_TRUE(aggressive_garp)

    return Test::PASSED;
}
