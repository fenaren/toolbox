#include <iostream>
#include <time.h>
#include <vector>

#include "PosixTimespec_test.hpp"

#include "PosixTimespec.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(PosixTimespec_test);

//==============================================================================
void PosixTimespec_test::addTestCases()
{
    ADD_TEST_CASE(Operators);
    ADD_TEST_CASE(BreakMeUp);
}

//==============================================================================
void PosixTimespec_test::Operators::addTestCases()
{
    ADD_TEST_CASE(Addition);
    ADD_TEST_CASE(Subtraction);
    ADD_TEST_CASE(GreaterThan);
    ADD_TEST_CASE(GreaterThanOrEqualTo);
    ADD_TEST_CASE(LessThan);
    ADD_TEST_CASE(LessThanOrEqualTo);
}

//==============================================================================
void PosixTimespec_test::Operators::Addition::addTestCases()
{
    ADD_TEST_CASE(Case1);
    ADD_TEST_CASE(Case2);
    ADD_TEST_CASE(Case3);
    ADD_TEST_CASE(Case4);
}

//==============================================================================
void PosixTimespec_test::Operators::Subtraction::addTestCases()
{
    ADD_TEST_CASE(Case1);
    ADD_TEST_CASE(Case2);
    ADD_TEST_CASE(Case3);
    ADD_TEST_CASE(Case4);
}

//==============================================================================
void PosixTimespec_test::Operators::GreaterThan::addTestCases()
{
    ADD_TEST_CASE(Case1);
    ADD_TEST_CASE(Case2);
    ADD_TEST_CASE(Case3);
}

//==============================================================================
void PosixTimespec_test::Operators::GreaterThanOrEqualTo::addTestCases()
{
    ADD_TEST_CASE(Case1);
    ADD_TEST_CASE(Case2);
    ADD_TEST_CASE(Case3);
}

//==============================================================================
void PosixTimespec_test::Operators::LessThan::addTestCases()
{
    ADD_TEST_CASE(Case1);
    ADD_TEST_CASE(Case2);
    ADD_TEST_CASE(Case3);
}

//==============================================================================
void PosixTimespec_test::Operators::LessThanOrEqualTo::addTestCases()
{
    ADD_TEST_CASE(Case1);
    ADD_TEST_CASE(Case2);
    ADD_TEST_CASE(Case3);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::Addition::Case1::body()
{
    return operatorTest(0, 0, 0, 1, 0, 1, ADDITION);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::Addition::Case2::body()
{
    return operatorTest(
        2346, 999999999, 1000, 40, 3347, 39, ADDITION);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::Addition::Case3::body()
{
    return operatorTest(5, 0, 2, 500000000, 7, 500000000, ADDITION);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::Addition::Case4::body()
{
    return operatorTest(1, 250000000, 0, 750000000, 2, 0, ADDITION);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::Subtraction::Case1::body()
{
    return operatorTest(
        0, 0, 0, 1, static_cast<time_t>(0) - 1, 999999999, SUBTRACTION);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::Subtraction::Case2::body()
{
    return operatorTest(
        2346, 999999999, 1000, 40, 1346, 999999959, SUBTRACTION);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::Subtraction::Case3::body()
{
    return operatorTest(
        5, 0, 2, 500000000, 2, 500000000, SUBTRACTION);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::Subtraction::Case4::body()
{
    return operatorTest(
        1, 250000000, 0, 750000000, 0, 500000000, SUBTRACTION);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::GreaterThan::Case1::body()
{
    return operatorTest(1, 0, 0, 1, true, GREATER_THAN);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::GreaterThan::Case2::body()
{
    return operatorTest(1, 0, 1, 0, false, GREATER_THAN);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::GreaterThan::Case3::body()
{
    return operatorTest(0, 1, 1, 0, false, GREATER_THAN);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::GreaterThanOrEqualTo::Case1::body()
{
    return operatorTest(1, 0, 0, 1, true, GREATER_THAN_OR_EQUAL_TO);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::GreaterThanOrEqualTo::Case2::body()
{
    return operatorTest(1, 0, 1, 0, true, GREATER_THAN_OR_EQUAL_TO);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::GreaterThanOrEqualTo::Case3::body()
{
    return operatorTest(0, 1, 1, 0, false, GREATER_THAN_OR_EQUAL_TO);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::LessThan::Case1::body()
{
    return operatorTest(1, 0, 0, 1, false, LESS_THAN);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::LessThan::Case2::body()
{
    return operatorTest(1, 0, 1, 0, false, LESS_THAN);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::LessThan::Case3::body()
{
    return operatorTest(0, 1, 1, 0, true, LESS_THAN);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::LessThanOrEqualTo::Case1::body()
{
    return operatorTest(1, 0, 0, 1, false, LESS_THAN_OR_EQUAL_TO);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::LessThanOrEqualTo::Case2::body()
{
    return operatorTest(1, 0, 1, 0, true, LESS_THAN_OR_EQUAL_TO);
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::LessThanOrEqualTo::Case3::body()
{
    return operatorTest(0, 1, 1, 0, true, LESS_THAN_OR_EQUAL_TO);
}

//==============================================================================
Test::Result PosixTimespec_test::BreakMeUp::body()
{
    timespec tp;

    // OTHER CASES
    // These are all tested against each other

    std::vector<timespec> timespecs;

    tp.tv_sec = 0;
    tp.tv_nsec = 0;
    timespecs.push_back(tp);

    tp.tv_sec = 0;
    tp.tv_nsec = 1;
    timespecs.push_back(tp);

    tp.tv_sec = 857693847;
    tp.tv_nsec = 736486;
    timespecs.push_back(tp);

    tp.tv_sec = 85769;
    tp.tv_nsec = 566486;
    timespecs.push_back(tp);

    tp.tv_sec = 8576946;
    tp.tv_nsec = 566486999;
    timespecs.push_back(tp);

    tp.tv_sec = 6;
    tp.tv_nsec = 999999999;
    timespecs.push_back(tp);

    std::vector<std::pair<unsigned int, unsigned int> > failed_cases;

    for (unsigned int i = 0; i < timespecs.size(); i++)
    {
        PosixTimespec ts1(timespecs[i]);

        for (unsigned int j = 0; j < timespecs.size(); j++)
        {
            PosixTimespec ts2(timespecs[j]);

            // Test addition
            PosixTimespec ts_sum1 = ts1 + ts2;
            PosixTimespec ts_sum2 = ts2 + ts1;

            timespec ts_sum1_tp;
            ts_sum1.getTimespec(ts_sum1_tp);

//            std::cout << timespecs[i].tv_sec << "("
//                      << timespecs[i].tv_nsec << ") + "
//                      << timespecs[j].tv_sec << "("
//                      << timespecs[j].tv_nsec << ") = "
//                      << ts_sum1_tp.tv_sec << "("
//                      << ts_sum1_tp.tv_nsec << ")\n";

            if (!(ts_sum1 == ts_sum2 && ts_sum2 == ts_sum1))
            {
                failed_cases.push_back(
                    std::pair<unsigned int, unsigned int>(i, j));

                continue;
            }

            // Test equality and inequality
            if (i == j)
            {
                if (!(ts1 == ts2 && ts2 == ts1 &&
                      // cppcheck-suppress duplicateExpression
                      timespecs[i] == ts2 && ts2 == timespecs[i] &&
                      // cppcheck-suppress duplicateExpression
                      ts1 == timespecs[j] && timespecs[j] == ts1))
                {
                    failed_cases.push_back(
                        std::pair<unsigned int, unsigned int>(i, j));
                }
            }
            else
            {
                if (!(ts1 != ts2 && ts2 != ts1 &&
                      // cppcheck-suppress duplicateExpression
                      timespecs[i] != ts2 && ts2 != timespecs[i] &&
                      // cppcheck-suppress duplicateExpression
                      ts1 != timespecs[j] && timespecs[j] != ts1))
                {
                    failed_cases.push_back(
                        std::pair<unsigned int, unsigned int>(i, j));
                }
            }
        }
    }

    std::cout << "Other failed cases: " << failed_cases.size() << "\n";

    MUST_BE_TRUE(failed_cases.size() == 0);

    PosixTimespec fromdblcheck(1.0);
    MUST_BE_TRUE(fromdblcheck.getSeconds() == 1);
    MUST_BE_TRUE(fromdblcheck.getNanoseconds() == 0);

    return Test::PASSED;
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::operatorTest(
    time_t              lhs_tv_sec,
    long                lhs_tv_nsec,
    time_t              rhs_tv_sec,
    long                rhs_tv_nsec,
    time_t              result_tv_sec,
    long                result_tv_nsec,
    ArithmeticOperation operation)
{
    // Create representations in the basic POSIX timespec and PosixTimespec
    PosixTimespec lhs;
    lhs.tp.tv_sec  = lhs_tv_sec;
    lhs.tp.tv_nsec = lhs_tv_nsec;

    timespec lhs_ts;
    lhs_ts.tv_sec  = lhs_tv_sec;
    lhs_ts.tv_nsec = lhs_tv_nsec;

    // Create representations in the basic POSIX timespec and PosixTimespec
    PosixTimespec rhs;
    rhs.tp.tv_sec  = rhs_tv_sec;
    rhs.tp.tv_nsec = rhs_tv_nsec;

    timespec rhs_ts;
    rhs_ts.tv_sec  = rhs_tv_sec;
    rhs_ts.tv_nsec = rhs_tv_nsec;

    // Do three separate tests of each operator.  One test uses a PosixTimespec
    // on both sides and the other two use a PosixTimespec on only one side.
    PosixTimespec result_bothsides;
    PosixTimespec result_lhs;
    PosixTimespec result_rhs;

    if (operation == ADDITION)
    {
        result_bothsides = lhs    + rhs;
        result_lhs       = lhs    + rhs_ts;
        result_rhs       = lhs_ts + rhs;
    }
    else if (operation == SUBTRACTION)
    {
        result_bothsides = lhs    - rhs;
        result_lhs       = lhs    - rhs_ts;
        result_rhs       = lhs_ts - rhs;
    }

    MUST_BE_TRUE(result_bothsides.tp.tv_sec  == result_tv_sec);
    MUST_BE_TRUE(result_bothsides.tp.tv_nsec == result_tv_nsec);

    MUST_BE_TRUE(result_lhs.tp.tv_sec  == result_tv_sec);
    MUST_BE_TRUE(result_lhs.tp.tv_nsec == result_tv_nsec);

    MUST_BE_TRUE(result_rhs.tp.tv_sec  == result_tv_sec);
    MUST_BE_TRUE(result_rhs.tp.tv_nsec == result_tv_nsec);

    return Test::PASSED;
}

//==============================================================================
Test::Result PosixTimespec_test::Operators::operatorTest(
    time_t              lhs_tv_sec,
    long                lhs_tv_nsec,
    time_t              rhs_tv_sec,
    long                rhs_tv_nsec,
    bool                result,
    ComparisonOperation operation)
{
    // Create representations in the basic POSIX timespec and PosixTimespec
    PosixTimespec lhs;
    lhs.tp.tv_sec  = lhs_tv_sec;
    lhs.tp.tv_nsec = lhs_tv_nsec;

    timespec lhs_ts;
    lhs_ts.tv_sec  = lhs_tv_sec;
    lhs_ts.tv_nsec = lhs_tv_nsec;

    // Create representations in the basic POSIX timespec and PosixTimespec
    PosixTimespec rhs;
    rhs.tp.tv_sec  = rhs_tv_sec;
    rhs.tp.tv_nsec = rhs_tv_nsec;

    timespec rhs_ts;
    rhs_ts.tv_sec  = rhs_tv_sec;
    rhs_ts.tv_nsec = rhs_tv_nsec;

    // Do three separate tests of each operator.  One test uses a PosixTimespec
    // on both sides and the other two use a PosixTimespec on only one side.
    bool result_bothsides = false;
    bool result_lhs       = false;
    bool result_rhs       = false;

    if (operation == GREATER_THAN)
    {
        result_bothsides = lhs    > rhs;
        result_lhs       = lhs    > rhs_ts;
        result_rhs       = lhs_ts > rhs;
    }
    else if (operation == GREATER_THAN_OR_EQUAL_TO)
    {
        result_bothsides = lhs    >= rhs;
        result_lhs       = lhs    >= rhs_ts;
        result_rhs       = lhs_ts >= rhs;
    }
    else if (operation == LESS_THAN)
    {
        result_bothsides = lhs    < rhs;
        result_lhs       = lhs    < rhs_ts;
        result_rhs       = lhs_ts < rhs;
    }
    else if (operation == LESS_THAN_OR_EQUAL_TO)
    {
        result_bothsides = lhs    <= rhs;
        result_lhs       = lhs    <= rhs_ts;
        result_rhs       = lhs_ts <= rhs;
    }

    MUST_BE_TRUE(result_bothsides == result);
    MUST_BE_TRUE(result_lhs       == result);
    MUST_BE_TRUE(result_rhs       == result);

    return Test::PASSED;
}
