#include <sstream>

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

//==============================================================================
// Prints internal state to the out string.  If units are known, units can be
// provided in the units string to be included in the output
//==============================================================================
void
OnlineStatistics::toString(std::string& out, const std::string& units) const
{
    std::ostringstream ostr;
    ostr << "Samples " << sample_count           << "\n"
         << "Mean    " << mean                   << " " << units << "\n"
         << "Stddev  " << getStandardDeviation() << " " << units << "\n"
         << "Min     " << minimum                << " " << units << "\n"
         << "Max     " << maximum                << " " << units << "\n";

    out = ostr.str();
}

//==============================================================================
// Textual output of OnlineStatistics internal state
//==============================================================================
std::ostream& operator<<(std::ostream& os, const OnlineStatistics& obj)
{
    std::string out;
    obj.toString(out);
    return os << out;
}
