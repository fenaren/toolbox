#ifndef LOG_TEST_HPP
#define LOG_TEST_HPP

#include "Test.hpp"

class LogTest : public Test
{
public:

    LogTest();
    ~LogTest();

    // Implements the test
    virtual Test::Result run();
};

#endif
