#include "FrameStatistics.hpp"

#include <limits>

//==============================================================================
// FrameStatistics constructor; initializes internal state by calling reset()
//==============================================================================
FrameStatistics::FrameStatistics()
{
    // Reset (initialize) all internal state
    reset();
}

//==============================================================================
// FrameStatistics destructor; does nothing
//==============================================================================
FrameStatistics::~FrameStatistics()
{
}

//==============================================================================
// Resets (initializes) internal state
//==============================================================================
void FrameStatistics::reset()
{
    sample_count   = 0;
    mean           = 0.0;
    varianceSource = 0.0;
    maximum        = 0.0;
    minimum        = std::numeric_limits<double>::max();
}

//==============================================================================
// Recalculates internal state, taking the provided unitless sample into account
//==============================================================================
void FrameStatistics::update(double sample)
{
    // We've been given a new sample so increment the sample counter
    ++sample_count;

    // Update running frame time statistics

    // We need to retain the old mean for the variance calculation below
    double last_mean = mean;

    // Update the mean
    mean += (sample - mean) / sample_count;

    // Update the variance
    varianceSource += (sample - mean) * (sample - last_mean);

    // Is this frame larger than any sample yet received?
    if (sample > maximum)
    {
        maximum = sample;
    }

    // Is this frame smaller than any sample yet received?
    if (sample < minimum)
    {
        minimum = sample;
    }
}
