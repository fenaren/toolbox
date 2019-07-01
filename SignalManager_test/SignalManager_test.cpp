#include <chrono>
#include <csignal>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <unordered_set>

#include "SignalManager.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TRIVIAL_TEST(SignalManager_test);

//==============================================================================
Test::Result SignalManager_test::body()
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

    // Give the signal manager a garbage signal and see what happens
    signal_manager->signal(999);

    // Give the signal manager another garbage signal and see what happens
    bool signal_caught = false;
    try
    {
        signal_manager->isSignalDelivered(1234);
    }
    catch (std::out_of_range& ex)
    {
        signal_caught = true;
    }
    MUST_BE_TRUE(signal_caught);

    // Test that we can signal and handle all the signals
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

        for (std::unordered_set<int>::const_iterator j =
                 supported_signals.begin();
             j != supported_signals.end();
             ++j)
        {
            // No signals should be delivered.  Ignore the possibility that some
            // third-party issued us a legitimate signal while we're doing this
            // test.
            MUST_BE_FALSE(signal_manager->isSignalDelivered(*j));
        }

        std::cout << "ok\n";
    }

    delete signal_manager;

    return Test::FAILED;
}
