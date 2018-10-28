#ifndef SIGNAL_MANAGER_TEST_HPP
#define SIGNAL_MANAGER_TEST_HPP

#include "Test.hpp"

class SignalManager_test : public Test
{
public:

    // Neither of these do anything
    SignalManager_test();
    ~SignalManager_test();

    // Implements the test
    virtual Test::Result run();
};

#endif
