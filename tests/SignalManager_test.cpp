#include <chrono>
#include <csignal>
#include <iostream>
#include <stdexcept>
#include <thread>
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
        std::cout << "Testing " << *i << " " << signal_name
                  << " ... " << std::flush;

        // Register this signal
        if (!signal_manager->registerSignal(*i))
        {
            std::cout << "COULD NOT REGISTER\n";
            continue;
        }

        // Raise the signal then wait for it
        bool signal_caught = false;
        MUST_BE_TRUE(raise(*i) == 0);
        for (unsigned int j = 0; j < 100; j++)
        {
            // Check for it every hundredth of a second for up to a whole second
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            if (signal_manager->isSignalDelivered(*i))
            {
                signal_caught = true;
                break;
            }
        }

        if (!signal_caught)
        {
            std::cout << "FAILED\n";
            delete signal_manager;
            return Test::FAILED;
        }

        std::cout << "ok\n";
    }

    delete signal_manager;

    return Test::PASSED;
}
