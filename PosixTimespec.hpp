#if !defined POSIX_TIMESPEC_HPP
#define POSIX_TIMESPEC_HPP

#include <time.h>

class PosixTimespec
{
public:

    explicit PosixTimespec(const timespec& tp);

    ~PosixTimespec();

    void getTimespec(timespec& tp) const;

    void setTimespec(const timespec& tp);

    PosixTimespec& operator=(const timespec& tp);

    PosixTimespec& operator-(const timespec& tp) const;

    PosixTimespec& operator-(const PosixTimespec& tp) const;

    PosixTimespec& operator+(const timespec& tp) const;

    PosixTimespec& operator+(const PosixTimespec& tp) const;

    bool operator==(const timespec& tp) const;

    bool operator==(const PosixTimespec& tp) const;

    bool operator!=(const timespec& tp) const;

    bool operator!=(const PosixTimespec& tp) const;

private:

    timespec tp;
};

inline void PosixTimespec::getTimespec(timespec& tp) const
{
    tp = this->tp;
}

inline void PosixTimespec::setTimespec(const timespec& tp)
{
    this->tp = tp;
}

#endif
