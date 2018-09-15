#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "OnlineStatistics.hpp"

bool withinEpsilonOf(double a, double b, double epsilon)
{
    return a <= (b + epsilon) && a >= (b - epsilon);
}

int main(int argc, char** argv)
{
    double epsilon = 0.00000001;

    // The test subject
    OnlineStatistics stats;

    std::ifstream resultstream("OnlineStatisticsTest.result.txt");
    if (resultstream.fail())
    {
        return 1;
    }

    double mean = 0.0;
    double stddev = 0.0;
    double min = 0.0;
    double max = 0.0;

    resultstream >> mean >> stddev >> min >> max;

    // This file has the raw data in it, one datum per line
    std::ifstream datastream("OnlineStatisticsTest.data.txt");
    if (datastream.fail())
    {
        return 1;
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

    return !(withinEpsilonOf(mean, stats.getMean(), epsilon) &&
             withinEpsilonOf(stddev, stats.getStandardDeviation(), epsilon) &&
             withinEpsilonOf(min, stats.getMinimumSample(), epsilon) &&
             withinEpsilonOf(max, stats.getMaximumSample(), epsilon));
}
