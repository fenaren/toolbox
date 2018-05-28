#if !defined POSIX_TIMESTAMP_HPP
#define POSIX_TIMESTAMP_HPP

#include <time.h>

class PosixTimestamp
{
public:

    PosixTimestamp(const timespec& tp);

    ~PosixTimestamp();

    void getTimestamp(timespec& ts) const;

    void setTimestamp(const timespec& ts);

private:

    timespec ts;
};

inline void PosixTimestamp::getTimestamp(timespec& ts) const
{
    ts = this->ts;
}

inline void PosixTimestamp::setTimestamp(const timespec& ts)
{
    this->ts = ts;
}

#endif
