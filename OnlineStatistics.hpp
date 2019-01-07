#if !defined ONLINE_STATISTICS_HPP
#define ONLINE_STATISTICS_HPP

#include <cmath>
#include <ostream>
#include <string>

// Maintains statistics which are kept up-to-date and available for reference
// during the runtime of a system (this is where the "online" in
// OnlineStatistics comes from), without requiring simultaneous access to every
// sample.

// New samples are provided using the update() function.  This function
// recalculates the statistics maintained internally to account for the new
// sample.  Statistics which take the new sample into account are available
// immediately after a call to update().

// Mean and variance calculations are done using Welford's online algorithm,
// meaning the samples that are provided to this class are not stored
// internally.  This class does not perform dynamic memory allocation nor does
// its memory footprint grow over time.
class OnlineStatistics
{
public:

    // OnlineStatistics constructor; initializes internal state by calling
    // reset()
    OnlineStatistics();

    // OnlineStatistics destructor; does nothing
    ~OnlineStatistics();

    // Resets (initializes) internal state
    void reset();

    // Recalculates internal state, taking the provided unitless sample into
    // account
    void update(double sample);

    // Returns the number of samples given to this class using the update()
    // function
    unsigned long getSampleCount() const;

    // Returns the current mean, taking into account all samples received using
    // the update() function
    double getMean() const;

    // Returns the current variance, taking into account all samples received
    // using the update() function
    double getVariance() const;

    // Returns the current standard deviation, taking into account all samples
    // received using the update() function
    double getStandardDeviation() const;

    // Returns the maximum (most positive) sample received, taking into account
    // all samples received using the update() function
    double getMaximumSample() const;

    // Returns the minimum (most negative) sample received, taking into account
    // all samples received using the update() function
    double getMinimumSample() const;

    // Prints internal state to the out string.  If units are known, units can
    // be provided in the units string to be included in the output
    void toString(std::string& out, const std::string& units = "") const;

private:

    // Incremented by one with each call to update(); represents the number of
    // samples provided using update()
    unsigned long sample_count;

    // The current running mean
    double mean;

    // The current running variance is derived from this by dividing this by
    // sample_count - 1.  This might not be the best name for this; I've seen
    // the theory name this variable "S" or "M2".
    double varianceSource;

    // The largest sample yet recorded
    double maximum;

    // The smallest sample yet recorded
    double minimum;

    // Disallow these for now; maybe these could be meaningfully implemented but
    // we'll save that for later
    OnlineStatistics(const OnlineStatistics&);
    OnlineStatistics& operator=(const OnlineStatistics&);
};

std::ostream& operator<<(std::ostream& os, const OnlineStatistics& obj);

inline unsigned long OnlineStatistics::getSampleCount() const
{
    return sample_count;
}

inline double OnlineStatistics::getMean() const
{
    return mean;
}

inline double OnlineStatistics::getVariance() const
{
    // Protect against divide-by-zero and underflow; variance is only meaningful
    // with two or more samples anyway
    if (sample_count <= 1)
    {
        return 0.0;
    }

    return varianceSource / (sample_count - 1);
}

inline double OnlineStatistics::getStandardDeviation() const
{
    return std::sqrt(getVariance());
}

inline double OnlineStatistics::getMaximumSample() const
{
    return maximum;
}

inline double OnlineStatistics::getMinimumSample() const
{
    return minimum;
}

#endif
