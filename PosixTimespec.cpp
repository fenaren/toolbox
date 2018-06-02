#include <cmath>
#include <istream>
#include <ostream>
#include <sstream>
#include <time.h>

#include "PosixTimespec.hpp"

const unsigned int PosixTimespec::nanoseconds_per_second = 1000000000;

//==============================================================================
// Initializes to 0s 0ns
//==============================================================================
PosixTimespec::PosixTimespec()
{
    tp.tv_sec  = 0;
    tp.tv_nsec = 0;
}

//==============================================================================
// Saves the provided timespec internally
//==============================================================================
PosixTimespec::PosixTimespec(const timespec& tp) :
    tp(tp)
{
}

//==============================================================================
// Converts to timespec before saving
//==============================================================================
PosixTimespec::PosixTimespec(double tp_sec)
{
    setDouble(tp_sec);
}

//==============================================================================
// Does nothing
//==============================================================================
PosixTimespec::~PosixTimespec()
{
}

//==============================================================================
// Returns double-precision floating point representation of timespec
//==============================================================================
double PosixTimespec::getDouble() const
{
    return static_cast<double>(this->tp.tv_sec) +
        (static_cast<double>(this->tp.tv_nsec) /
         static_cast<double>(nanoseconds_per_second));
}

//==============================================================================
// Sets timespec based on provided double-precision floating point number
//==============================================================================
bool PosixTimespec::setDouble(double tp_dbl)
{
    // This class can't represent values less than zero
    if (tp_dbl < 0.0)
    {
        return false;
    }

    double fractional_part = 0.0;
    this->tp.tv_sec  = std::modf(tp_dbl, &fractional_part);
    this->tp.tv_nsec = fractional_part *
        static_cast<double>(nanoseconds_per_second);

    return true;
}

//==============================================================================
// Does what you would expect
//==============================================================================
PosixTimespec& PosixTimespec::operator=(const timespec& tp)
{
    this->tp.tv_sec  = tp.tv_sec;
    this->tp.tv_nsec = tp.tv_nsec;

    return *this;
}

//==============================================================================
// Performs integer addition so no data loss occurs; tv_nsec overflows and adds
// to tv_sec as one would expect
//==============================================================================
PosixTimespec& PosixTimespec::operator+=(const timespec& tp)
{
    this->tp.tv_sec += tp.tv_sec;
    this->tp.tv_nsec += tp.tv_nsec;

    if (this->tp.tv_nsec >= nanoseconds_per_second)
    {
        this->tp.tv_nsec -= nanoseconds_per_second;
        this->tp.tv_sec += 1;
    }

    return *this;
}

//==============================================================================
// Does what you would expect
//==============================================================================
PosixTimespec& PosixTimespec::operator+=(const PosixTimespec& tp)
{
    timespec tp_temp;
    tp.getTimespec(tp_temp);

    return operator+=(tp_temp);
}

//==============================================================================
// Does what you would expect
//==============================================================================
PosixTimespec& PosixTimespec::operator-=(const timespec& tp)
{
}

//==============================================================================
// Does what you would expect
//==============================================================================
PosixTimespec& PosixTimespec::operator-=(const PosixTimespec& tp)
{
}

//==============================================================================
// Does what you would expect
//==============================================================================
PosixTimespec operator+(PosixTimespec lhs, const PosixTimespec& rhs)
{
    lhs += rhs;
    return lhs;
}

//==============================================================================
// Does what you would expect
//==============================================================================
PosixTimespec operator+(PosixTimespec lhs, const timespec& rhs)
{
    lhs += rhs;
    return lhs;
}

//==============================================================================
// Does what you would expect
//==============================================================================
PosixTimespec operator+(timespec lhs, const PosixTimespec& rhs)
{
    // Addition is symmetric
    return operator+(rhs, lhs);
}

//==============================================================================
// Does what you would expect
//==============================================================================
PosixTimespec operator-(PosixTimespec lhs, const PosixTimespec& rhs)
{
    lhs -= rhs;
    return lhs;
}

//==============================================================================
// Does what you would expect
//==============================================================================
PosixTimespec operator-(PosixTimespec lhs, const timespec& rhs)
{
    lhs -= rhs;
    return lhs;
}

//==============================================================================
// Does what you would expect
//==============================================================================
PosixTimespec operator-(timespec lhs, const PosixTimespec& rhs)
{
    lhs -= rhs;
    return lhs;
}

//==============================================================================
// Does what you would expect
//==============================================================================
bool operator==(const PosixTimespec& lhs, const PosixTimespec& rhs)
{
    timespec lhs_tp;
    timespec rhs_tp;

    lhs.getTimespec(lhs_tp);
    rhs.getTimespec(rhs_tp);

    return lhs_tp.tv_sec == rhs_tp.tv_sec && lhs_tp.tv_nsec == rhs_tp.tv_nsec;
}

//==============================================================================
// Does what you would expect
//==============================================================================
bool operator==(const PosixTimespec& lhs, const timespec& rhs)
{
    return lhs == PosixTimespec(rhs);
}

//==============================================================================
// Does what you would expect
//==============================================================================
bool operator==(const timespec& lhs, const PosixTimespec& rhs)
{
    return PosixTimespec(lhs) == rhs;
}

//==============================================================================
// Does what you would expect
//==============================================================================
bool operator!=(const PosixTimespec& lhs, const PosixTimespec& rhs)
{
    return !(lhs == rhs);
}

//==============================================================================
// Does what you would expect
//==============================================================================
bool operator!=(const PosixTimespec& lhs, const timespec& rhs)
{
    return !(lhs == rhs);
}

//==============================================================================
// Does what you would expect
//==============================================================================
bool operator!=(const timespec& lhs, const PosixTimespec& rhs)
{
    return !(lhs == rhs);
}


//==============================================================================
// Writes a string representation
//==============================================================================
std::ostream& operator<<(std::ostream& os, PosixTimespec& posix_timespec)
{
    return os << posix_timespec.getDouble();
}

//==============================================================================
// Reads a string representation
//==============================================================================
std::istream& operator>>(std::istream& is, PosixTimespec& posix_timespec)
{
    // Get the number as a string
    std::string posix_timespec_str;
    is >> posix_timespec_str;

    // Convert to double and internalize
    std::istringstream to_double(posix_timespec_str);
    double posix_timespec_dbl = 0.0;
    to_double >> posix_timespec_dbl;

    posix_timespec.setDouble(posix_timespec_dbl);

    return is;
}
