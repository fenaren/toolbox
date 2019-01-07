#if !defined POSIX_TIMESPEC_HPP
#define POSIX_TIMESPEC_HPP

#include <istream>
#include <ostream>
#include <sys/types.h>
#include <time.h>

class PosixTimespec
{
public:

    // Initializes to 0s 0ns
    PosixTimespec();

    // Saves the proviced timespec internally
    explicit PosixTimespec(const timespec& tp);

    // Converts to timespec before saving
    explicit PosixTimespec(double tp_sec);

    // Copy constructor
    PosixTimespec(const PosixTimespec&);

    // Initializes to tv_sec tv_nsec
    PosixTimespec(time_t tv_sec, long tv_nsec);

    // For converting PosixTimespecs to other types
    operator double() const;
    operator timespec() const;

    // Does nothing
    ~PosixTimespec();

    // Returns internally-saved timespec
    void getTimespec(timespec& tp) const;

    // Sets internally-saved timespec
    void setTimespec(const timespec& tp);

    // Returns current value of timespec seconds field
    time_t getSeconds() const;

    // Sets the timespec seconds field
    void setSeconds(time_t s);

    // Returns the timespec nanoseconds field; unlike seconds this field is
    // explicitly specified in POSIX as long
    long getNanoseconds() const;

    // Sets the timespec nanoseconds field; unlike seconds this field is
    // explicitly specified in POSIX as long
    void setNanoseconds(long ns);

    // tp timespec to a double-precision floating point
    double toDouble() const;

    // Sets self based on provided double-precision floating point number
    bool fromDouble(double tp_dbl);

    PosixTimespec& operator=(double tp_dbl);
    PosixTimespec& operator=(const timespec& tp);
    PosixTimespec& operator=(const PosixTimespec&);

    // Performs integer addition so no data loss occurs during the addition
    // operation itself; tv_nsec overflows and adds to tv_sec as one would
    // expect
    PosixTimespec& operator+=(double tp_dbl);
    PosixTimespec& operator+=(const timespec& tp);
    PosixTimespec& operator+=(const PosixTimespec& tp);

    // Performs integer subtraction so no data loss occurs during the
    // subtraction operation itself; tv_nsec underflows and adds to tv_sec as
    // one would expect
    PosixTimespec& operator-=(double tp_dbl);
    PosixTimespec& operator-=(const timespec& tp);
    PosixTimespec& operator-=(const PosixTimespec& tp);

private:

    // POSIX-defined
    timespec tp;

    static const unsigned int nanoseconds_per_second;
};

PosixTimespec operator+(PosixTimespec lhs, const PosixTimespec& rhs);
PosixTimespec operator+(PosixTimespec lhs, const timespec&      rhs);
PosixTimespec operator+(timespec      lhs, const PosixTimespec& rhs);
PosixTimespec operator+(PosixTimespec lhs, double               rhs);
PosixTimespec operator+(double        lhs, const PosixTimespec& rhs);

PosixTimespec operator-(PosixTimespec lhs, const PosixTimespec& rhs);
PosixTimespec operator-(PosixTimespec lhs, const timespec&      rhs);
PosixTimespec operator-(timespec      lhs, const PosixTimespec& rhs);
PosixTimespec operator-(PosixTimespec lhs, double               rhs);
PosixTimespec operator-(double        lhs, const PosixTimespec& rhs);

bool operator==(const PosixTimespec& lhs, const PosixTimespec& rhs);
bool operator==(const PosixTimespec& lhs, const timespec&      rhs);
bool operator==(const timespec&      lhs, const PosixTimespec& rhs);
bool operator==(PosixTimespec        lhs, double               rhs);
bool operator==(double               lhs, const PosixTimespec& rhs);

bool operator!=(const PosixTimespec& lhs, const PosixTimespec& rhs);
bool operator!=(const PosixTimespec& lhs, const timespec&      rhs);
bool operator!=(const timespec&      lhs, const PosixTimespec& rhs);
bool operator!=(PosixTimespec        lhs, double               rhs);
bool operator!=(double               lhs, const PosixTimespec& rhs);

bool operator<(const PosixTimespec& lhs, const PosixTimespec& rhs);
bool operator<(const PosixTimespec& lhs, const timespec&      rhs);
bool operator<(const timespec&      lhs, const PosixTimespec& rhs);
bool operator<(PosixTimespec        lhs, double               rhs);
bool operator<(double               lhs, const PosixTimespec& rhs);

bool operator>(const PosixTimespec& lhs, const PosixTimespec& rhs);
bool operator>(const PosixTimespec& lhs, const timespec&      rhs);
bool operator>(const timespec&      lhs, const PosixTimespec& rhs);
bool operator>(PosixTimespec        lhs, double               rhs);
bool operator>(double               lhs, const PosixTimespec& rhs);

bool operator<=(const PosixTimespec& lhs, const PosixTimespec& rhs);
bool operator<=(const PosixTimespec& lhs, const timespec&      rhs);
bool operator<=(const timespec&      lhs, const PosixTimespec& rhs);
bool operator<=(PosixTimespec        lhs, double               rhs);
bool operator<=(double               lhs, const PosixTimespec& rhs);

bool operator>=(const PosixTimespec& lhs, const PosixTimespec& rhs);
bool operator>=(const PosixTimespec& lhs, const timespec&      rhs);
bool operator>=(const timespec&      lhs, const PosixTimespec& rhs);
bool operator>=(PosixTimespec        lhs, double               rhs);
bool operator>=(double               lhs, const PosixTimespec& rhs);

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

inline time_t PosixTimespec::getSeconds() const
{
    return tp.tv_sec;
}

inline void PosixTimespec::setSeconds(time_t s)
{
    this->tp.tv_sec = s;
}

inline long PosixTimespec::getNanoseconds() const
{
    return tp.tv_nsec;
}

inline void PosixTimespec::setNanoseconds(long ns)
{
    this->tp.tv_nsec = ns;
}

#endif
