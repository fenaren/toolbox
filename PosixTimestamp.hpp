#if !defined POSIX_TIMESTAMP_HPP
#define POSIX_TIMESTAMP_HPP

#include <time.h>

class PosixTimestamp
{
public:

    PosixTimestamp(const timespec& tp);

private:

    timespec ts;
};

#endif
