#if !defined POSIX_TIMESPEC_HPP
#define POSIX_TIMESPEC_HPP

#include <istream>
#include <ostream>
#include <time.h>

class PosixTimespec
{
public:

    // Initializes to 0s 0ns
    PosixTimespec();

    // Saves the proviced timespec internally
    explicit PosixTimespec(const timespec& tp);

    // Converts to timespec before saving
    PosixTimespec(double tp_sec);

    // Does nothing
    ~PosixTimespec();

    // Returns internally-saved timespec
    void getTimespec(timespec& tp) const;

    // Sets internally-saved timespec
    void setTimespec(const timespec& tp);

    // Converts timespec to a double-precision floating point
    double getDouble() const;

    // Sets self based on provided double-precision floating point number
    bool setDouble(double tp_dbl);

    PosixTimespec& operator=(const timespec& tp);

    // Performs integer addition so no data loss occurs; tv_nsec overflows and
    // adds to tv_sec as one would expect
    PosixTimespec& operator+=(const timespec& tp);
    PosixTimespec& operator+=(const PosixTimespec& tp);

private:

    // POSIX-defined
    timespec tp;

    static const unsigned int nanoseconds_per_second;
};

PosixTimespec operator+(PosixTimespec lhs,  const PosixTimespec& rhs);
PosixTimespec operator+(PosixTimespec lhs,  const timespec& rhs);
PosixTimespec operator+(timespec lhs,       const PosixTimespec& rhs);

bool operator==(const PosixTimespec& lhs, const PosixTimespec& rhs);
bool operator==(const PosixTimespec& lhs, const timespec& rhs);
bool operator==(const timespec& lhs,      const PosixTimespec& rhs);

bool operator!=(const PosixTimespec& lhs, const PosixTimespec& rhs);
bool operator!=(const PosixTimespec& lhs, const timespec& rhs);
bool operator!=(const timespec& lhs,      const PosixTimespec& rhs);

// Writes a string representation
std::ostream& operator<<(std::ostream& os, PosixTimespec& posix_timespec);

// Reads a string representation
std::istream& operator>>(std::istream& is, PosixTimespec& posix_timespec);

inline void PosixTimespec::getTimespec(timespec& tp) const
{
    tp = this->tp;
}

inline void PosixTimespec::setTimespec(const timespec& tp)
{
    this->tp = tp;
}

#endif
