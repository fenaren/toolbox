#include "OnlineStatistics.hpp"

//==============================================================================
// OnlineStatistics constructor; initializes internal state by calling reset()
//==============================================================================
OnlineStatistics::OnlineStatistics()
{
    // Reset (initialize) all internal state
    reset();
}

//==============================================================================
// OnlineStatistics destructor; does nothing
//==============================================================================
OnlineStatistics::~OnlineStatistics()
{
}

//==============================================================================
// Resets (initializes) internal state
//==============================================================================
void OnlineStatistics::reset()
{
    sample_count   = 0;
    mean           = 0.0;
    varianceSource = 0.0;
    maximum        = 0.0;
    minimum        = 0.0;
}

//==============================================================================
// Recalculates internal state, taking the provided unitless sample into account
//==============================================================================
void OnlineStatistics::update(double sample)
{
    // We've been given a new sample so increment the sample counter
    ++sample_count;

    // Update statistics

    // We need to retain the old mean for the variance calculation below
    double last_mean = mean;

    // Update the mean
    mean += (sample - mean) / sample_count;

    // Update the variance
    varianceSource += (sample - mean) * (sample - last_mean);

    // If this sample is the only sample we've ever received then it must be
    // both the smallest and largest sample ever received
    if (sample_count == 1)
    {
        maximum = sample;
        minimum = sample;
    }
    else
    {
        // Is this sample larger than any sample yet received?
        if (sample > maximum)
        {
            maximum = sample;
        }

        // Is this sample smaller than any sample yet received?
        if (sample < minimum)
        {
            minimum = sample;
        }
    }
}
