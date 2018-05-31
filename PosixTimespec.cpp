#include <time.h>

#include "PosixTimespec.hpp"

const unsigned int PosixTimespec::nanoseconds_per_second = 1000000000;

//==============================================================================
// Saves the provided timespec internally
//==============================================================================
PosixTimespec::PosixTimespec(const timespec& tp) :
    tp(tp)
{
}

//==============================================================================
// Does nothing
//==============================================================================
PosixTimespec::~PosixTimespec()
{
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
