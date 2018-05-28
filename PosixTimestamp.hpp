#if !defined POSIX_TIMESTAMP_HPP
#define POSIX_TIMESTAMP_HPP

#include <time.h>

class PosixTimestamp
{
public:

    explicit PosixTimestamp(const timespec& tp);

    ~PosixTimestamp();

    void getTimestamp(timespec& tp) const;

    void setTimestamp(const timespec& tp);

    PosixTimestamp& operator=(const timespec& tp);

private:

    timespec tp;
};

inline void PosixTimestamp::getTimestamp(timespec& tp) const
{
    tp = this->tp;
}

inline void PosixTimestamp::setTimestamp(const timespec& tp)
{
    this->tp = tp;
}

#endif
