#ifndef LOG_TEST_HPP
#define LOG_TEST_HPP

#include "Test.hpp"

class Log_test : public Test
{
public:

    // Neither of these do anything
    Log_test();
    ~Log_test();

    // Implements the test
    virtual Test::Result run();
};

#endif