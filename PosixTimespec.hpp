#if !defined POSIX_TIMESPEC_HPP
#define POSIX_TIMESPEC_HPP

#include <time.h>

class PosixTimespec
{
public:

    // Saves the proviced timespec internally
    explicit PosixTimespec(const timespec& tp);

    // Does nothing
    ~PosixTimespec();

    // Returns internally-saved timespec
    void getTimespec(timespec& tp) const;

    // Sets internally-saved timespec
    void setTimespec(const timespec& tp);

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

inline void PosixTimespec::getTimespec(timespec& tp) const
{
    tp = this->tp;
}

inline void PosixTimespec::setTimespec(const timespec& tp)
{
    this->tp = tp;
}

#endif
