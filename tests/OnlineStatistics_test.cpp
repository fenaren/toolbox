#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "OnlineStatistics.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"
#include "misc.hpp"

TRIVIAL_TEST(OnlineStatistics_test);

//==============================================================================
Test::Result OnlineStatistics_test::run()
{
    const double EPSILON = 0.00000001;

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

    if (misc::withinEpsilonOf(mean,   stats.getMean(),              EPSILON) &&
        misc::withinEpsilonOf(stddev, stats.getStandardDeviation(), EPSILON) &&
        misc::withinEpsilonOf(min,    stats.getMinimumSample(),     EPSILON) &&
        misc::withinEpsilonOf(max,    stats.getMaximumSample(),     EPSILON))
    {
        return Test::PASSED;
    }

    return Test::FAILED;
}

//==============================================================================
