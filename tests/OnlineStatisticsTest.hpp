#ifndef ONLINE_STATISTICS_TEST_HPP
#define ONLINE_STATISTICS_TEST_HPP

#include "Test.hpp"

class OnlineStatisticsTest : public Test
{
public:

    OnlineStatisticsTest();
    ~OnlineStatisticsTest();

    // Implements the test
    virtual Test::Result run();

private:

    bool withinEpsilonOf(double a, double b, double epsilon);
};

#endif
