#ifndef POSIX_TIMESPEC_TEST_HPP
#define POSIX_TIMESPEC_TEST_HPP

#include "Test.hpp"

class PosixTimespecTest : public Test
{
public:

    enum Greater
    {
        LHS,
        RHS,
        EQUAL
    };

    struct TimespecGtlt
    {
        timespec lhs;
        timespec rhs;
        Greater  greater;
    };

    struct TimespecTuple
    {
        timespec lhs;
        timespec rhs;
        timespec result;
    };

    PosixTimespecTest();
    ~PosixTimespecTest();

    // Implements the test
    virtual Test::Result run();
};

#endif
