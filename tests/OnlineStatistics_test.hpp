#ifndef ONLINE_STATISTICS_TEST_HPP
#define ONLINE_STATISTICS_TEST_HPP

#include "Test.hpp"

class OnlineStatistics_test : public Test
{
public:

    OnlineStatistics_test();
    ~OnlineStatistics_test();

    // Implements the test
    virtual Test::Result run();

private:

    bool withinEpsilonOf(double a, double b, double epsilon);
};

#endif
