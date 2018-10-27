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
    SignalManager signal_manager;

    std::unordered_set<int> supported_signals;
    signal_manager.getSupportedSignals(supported_signals);
    std::cout << supported_signals.size() << "\n";
    
    /*for (std::unordered_set<int>::const_iterator i = supported_signals.begin();
         i != supported_signals.end();
         ++i)
    {
    }*/
    


    return Test::PASSED;
}
