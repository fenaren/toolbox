#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "OnlineStatistics_test.hpp"

#include "OnlineStatistics.hpp"
#include "Test.hpp"
#include "TestProgramMain.hpp"

TEST_PROGRAM_MAIN(OnlineStatistics_test);

//==============================================================================
OnlineStatistics_test::OnlineStatistics_test()
{
}

//==============================================================================
OnlineStatistics_test::~OnlineStatistics_test()
{
}

//==============================================================================
Test::Result OnlineStatistics_test::run()
{
    double epsilon = 0.00000001;

    // The test subject
    OnlineStatistics stats;

    std::ifstream resultstream("OnlineStatistics_test.result.txt");
    if (resultstream.fail())
    {
        return Test::FAILED;
    }

    double mean = 0.0;
    double stddev = 0.0;
    double min = 0.0;
    double max = 0.0;

    resultstream >> mean >> stddev >> min >> max;

    // This file has the raw data in it, one datum per line
    std::ifstream datastream("OnlineStatistics_test.data.txt");
    if (datastream.fail())
    {
        return Test::FAILED;
    }

    // Suck in all the data
    double datum;
    while(datastream)
    {
        datastream >> datum;

        if (datastream)
        {
            stats.update(datum);
        }
    }

    std::cout << std::setprecision(15)
              << "Samples " << stats.getSampleCount() << "\n"
              << "Mean "    << stats.getMean() << "\n"
              << "Stddev "  << stats.getStandardDeviation() << "\n"
              << "Min "     << stats.getMinimumSample() << "\n"
              << "Max "     << stats.getMaximumSample() << "\n";

    if (withinEpsilonOf(mean,   stats.getMean(),              epsilon) &&
        withinEpsilonOf(stddev, stats.getStandardDeviation(), epsilon) &&
        withinEpsilonOf(min,    stats.getMinimumSample(),     epsilon) &&
        withinEpsilonOf(max,    stats.getMaximumSample(),     epsilon))
    {
        return Test::PASSED;
    }

    return Test::FAILED;
}

//==============================================================================
bool OnlineStatistics_test::withinEpsilonOf(double a, double b, double epsilon)
{
    return a <= (b + epsilon) && a >= (b - epsilon);
}
