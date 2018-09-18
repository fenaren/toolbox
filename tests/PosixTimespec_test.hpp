#ifndef POSIX_TIMESPEC_TEST_HPP
#define POSIX_TIMESPEC_TEST_HPP

#include "Test.hpp"

class PosixTimespec_test : public Test
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

    // Neither of these do anything
    PosixTimespec_test();
    ~PosixTimespec_test();

    // Implements the test
    virtual Test::Result run();
};

#endif
