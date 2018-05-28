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

    PosixTimespec& operator+=(const timespec& tp);
    PosixTimespec& operator+=(const PosixTimespec& tp);

    //PosixTimespec& operator-=(const timespec& tp);
    //PosixTimespec& operator-=(const PosixTimespec& tp);

private:

    timespec tp;
};

PosixTimespec operator+(PosixTimespec lhs,  const PosixTimespec& rhs);
PosixTimespec operator+(PosixTimespec lhs,  const timespec& rhs);
PosixTimespec operator+(timespec lhs,       const PosixTimespec& rhs);

//PosixTimespec operator-(PosixTimespec lhs,  const PosixTimespec& rhs);
//PosixTimespec operator-(PosixTimespec lhs,  const timespec& rhs);
//PosixTimespec operator-(timespec lhs,       const PosixTimespec& rhs);

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
