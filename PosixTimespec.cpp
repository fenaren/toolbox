#include <climits>
#include <time.h>

#include "PosixTimespec.hpp"

//==============================================================================
//
//==============================================================================
PosixTimespec::PosixTimespec(const timespec& tp) :
    tp(tp)
{
}

//==============================================================================
//
//==============================================================================
PosixTimespec::~PosixTimespec()
{
}

//==============================================================================
//
//==============================================================================
PosixTimespec& PosixTimespec::operator=(const timespec& tp)
{
    this->tp.tv_sec  = tp.tv_sec;
    this->tp.tv_nsec = tp.tv_nsec;

    return *this;
}

//==============================================================================
//
//==============================================================================
PosixTimespec& PosixTimespec::operator+=(const timespec& tp)
{
    this->tp.tv_sec += tp.tv_sec;
    this->tp.tv_nsec += tp.tv_nsec;

    // Do we need to add one to tv_sec?
    if (this->tp.tv_nsec >= 1e9 - tp.tv_nsec)
    {
        this->tp.tv_sec += 1;
    }

    return *this;
}

//==============================================================================
//
//==============================================================================
PosixTimespec& PosixTimespec::operator+=(const PosixTimespec& tp)
{
    timespec tp_temp;
    tp.getTimespec(tp_temp);

    return operator+=(tp_temp);
}

//==============================================================================
//
//==============================================================================
/*PosixTimespec& PosixTimespec::operator-=(const timespec& tp)
{
    // Do the subtraction

    //return *this;
}

//==============================================================================
//
//==============================================================================
PosixTimespec& PosixTimespec::operator-=(const PosixTimespec& tp)
{
    timespec tp_temp;
    tp.getTimespec(tp_temp);

    return operator-=(tp_temp);
    }*/

//==============================================================================
//
//==============================================================================
PosixTimespec operator+(PosixTimespec lhs, const PosixTimespec& rhs)
{
    lhs += rhs;
    return lhs;
}

//==============================================================================
//
//==============================================================================
PosixTimespec operator+(PosixTimespec lhs, const timespec& rhs)
{
    lhs += rhs;
    return lhs;
}

//==============================================================================
//
//==============================================================================
PosixTimespec operator+(timespec lhs, const PosixTimespec& rhs)
{
    // Addition is symmetric
    return operator+(rhs, lhs);
}

//==============================================================================
//
//==============================================================================
/*PosixTimespec operator-(PosixTimespec lhs, const PosixTimespec& rhs)
{
    lhs -= rhs;
    return lhs;
}

//==============================================================================
//
//==============================================================================
PosixTimespec operator-(PosixTimespec lhs, const timespec& rhs)
{
    lhs -= rhs;
    return lhs;
}

//==============================================================================
//
//==============================================================================
PosixTimespec operator-(timespec lhs, const PosixTimespec& rhs)
{
    // TODO
    }*/

//==============================================================================
//
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
//
//==============================================================================
bool operator==(const PosixTimespec& lhs, const timespec& rhs)
{
    return lhs == PosixTimespec(rhs);
}

//==============================================================================
//
//==============================================================================
bool operator==(const timespec& lhs, const PosixTimespec& rhs)
{
    return PosixTimespec(lhs) == rhs;
}

//==============================================================================
//
//==============================================================================
bool operator!=(const PosixTimespec& lhs, const PosixTimespec& rhs)
{
    return !(lhs == rhs);
}

//==============================================================================
//
//==============================================================================
bool operator!=(const PosixTimespec& lhs, const timespec& rhs)
{
    return !(lhs == rhs);
}

//==============================================================================
//
//==============================================================================
bool operator!=(const timespec& lhs, const PosixTimespec& rhs)
{
    return !(lhs == rhs);
}
