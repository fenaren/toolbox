#include <iomanip>
#include <iostream>
#include <unordered_set>

#include "SignalManager_test.hpp"

#include "SignalManager.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(SignalManager_test);

//==============================================================================
SignalManager_test::SignalManager_test()
{
}

//==============================================================================
SignalManager_test::~SignalManager_test()
{
}

//==============================================================================
Test::Result SignalManager_test::run()
{
    SignalManager* signal_manager = 0;
    try
    {
        signal_manager = new SignalManager();
    }
    catch (std::runtime_error& ex)
    {
        return Test::SKIPPED;
    }

    std::unordered_set<int> supported_signals;
    signal_manager->getSupportedSignals(supported_signals);
    std::cout << supported_signals.size() << " supported signal(s)\n";

    for (std::unordered_set<int>::const_iterator i = supported_signals.begin();
         i != supported_signals.end();
         ++i)
    {
        std::string signal_name;
        signal_manager->getSignalName(*i, signal_name);
        std::cout << std::setw(2) << *i << " " << signal_name << "\n";
    }

    return Test::PASSED;
}
