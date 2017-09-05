#if !defined FRAME_STATISTICS_HPP
#define FRAME_STATISTICS_HPP

#include <cmath>

// Maintains a set of statistics useful in determining the chronological
// performance of a rate-based system  Mean and variance calculations are done
// using Welford's online algorithm, meaning the frame time samples that are
// provided to this class are not stored internally.  This class does not
// perform dynamic memory allocation nor does its memory footprint grow over
// time.
class FrameStatistics
{
public:

    // FrameStatistics constructor; initializes internal state by calling
    // reset()
    FrameStatistics();

    // Frame Statistics destructor; does nothing
    ~FrameStatistics();

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

private:

    // Incremented by one with each call to update(); represents the number of
    // provided frame time samples
    unsigned long sample_count;

    // The current running mean
    double mean;

    // The current running variance is derived from this by dividing this by
    // sample_count - 1.  This might not be the best name for this; I've seen
    // the theory name this variable "S" or "M2".
    double varianceSource;

    // The largest frame time yet recorded
    double maximum;

    // The smallest frame time yet recorded
    double minimum;
};

inline unsigned long FrameStatistics::getSampleCount() const
{
    return sample_count;
}

inline double FrameStatistics::getMean() const
{
    return mean;
}

inline double FrameStatistics::getVariance() const
{
    // Protect against divide-by-zero and underflow; variance is only meaningful
    // with two or more samples anyway
    if (sample_count <= 1)
    {
        return 0.0;
    }

    return varianceSource / (sample_count - 1);
}

inline double FrameStatistics::getStandardDeviation() const
{
    return std::sqrt(getVariance());
}

inline double FrameStatistics::getMaximumSample() const
{
    return maximum;
}

inline double FrameStatistics::getMinimumSample() const
{
    return minimum;
}

#endif
