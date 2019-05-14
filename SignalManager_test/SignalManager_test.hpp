#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(SignalManager_test)

    TEST(PrintSupportedSignalCount)
    TEST(SignalUnknownSignal)
    TEST(CheckUnknownSignalDelivered)
    TEST(GenerateAllSignals)

TEST_CASES_END(SignalManager_test)

#define GET_SIGNAL_MANAGER(signal_manager)      \
    try                                         \
    {                                           \
        signal_manager = new SignalManager();   \
    }                                           \
    catch (std::runtime_error& ex)              \
    {                                           \
        return Test::SKIPPED;                   \
    }
