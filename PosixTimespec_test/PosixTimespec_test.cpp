#include <iostream>
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
    ADD_TEST_CASE(Operator);
    ADD_TEST_CASE(BreakMeUp);
}

//==============================================================================
void PosixTimespec_test::Operator::addTestCases()
{
    ADD_TEST_CASE(Addition);
    ADD_TEST_CASE(Subtraction);
    ADD_TEST_CASE(GreaterThan);
    ADD_TEST_CASE(GreaterThanEqualTo);
    ADD_TEST_CASE(LessThan);
    ADD_TEST_CASE(LessThanEqualTo);
}

//==============================================================================
void PosixTimespec_test::Operator::Addition::addTestCases()
{
    ADD_TEST_CASE(Case1);
    ADD_TEST_CASE(Case2);
    ADD_TEST_CASE(Case3);
    ADD_TEST_CASE(Case4);
}

//==============================================================================
Test::Result PosixTimespec_test::Operator::Addition::Case1::body()
{
    PosixTimespec lhs;
    lhs.tp.tv_sec  = 0;
    lhs.tp.tv_nsec = 0;

    PosixTimespec rhs;
    rhs.tp.tv_sec  = 0;
    rhs.tp.tv_nsec = 1;

    PosixTimespec sum = lhs + rhs;

    MUST_BE_TRUE(sum.tp.tv_sec  == 0);
    MUST_BE_TRUE(sum.tp.tv_nsec == 1);

    return Test::PASSED;
}

//==============================================================================
Test::Result PosixTimespec_test::Operator::Addition::Case2::body()
{
    PosixTimespec lhs;
    lhs.tp.tv_sec  = 2346;
    lhs.tp.tv_nsec = 999999999;

    PosixTimespec rhs;
    rhs.tp.tv_sec  = 1000;
    rhs.tp.tv_nsec = 40;

    PosixTimespec sum = lhs + rhs;

    MUST_BE_TRUE(sum.tp.tv_sec  == 3347);
    MUST_BE_TRUE(sum.tp.tv_nsec == 39);

    return Test::PASSED;
}

//==============================================================================
Test::Result PosixTimespec_test::Operator::Addition::Case3::body()
{
    PosixTimespec lhs;
    lhs.tp.tv_sec  = 5;
    lhs.tp.tv_nsec = 0;

    PosixTimespec rhs;
    rhs.tp.tv_sec  = 2;
    rhs.tp.tv_nsec = 500000000;

    PosixTimespec sum = lhs + rhs;

    MUST_BE_TRUE(sum.tp.tv_sec  == 7);
    MUST_BE_TRUE(sum.tp.tv_nsec == 500000000);

    return Test::PASSED;
}

//==============================================================================
Test::Result PosixTimespec_test::Operator::Addition::Case4::body()
{
    PosixTimespec lhs;
    lhs.tp.tv_sec  = 1;
    lhs.tp.tv_nsec = 250000000;

    PosixTimespec rhs;
    rhs.tp.tv_sec  = 0;
    rhs.tp.tv_nsec = 750000000;

    PosixTimespec sum = lhs + rhs;

    MUST_BE_TRUE(sum.tp.tv_sec  == 2);
    MUST_BE_TRUE(sum.tp.tv_nsec == 0);

    return Test::PASSED;
}

//==============================================================================
Test::Result PosixTimespec_test::Operator::Subtraction::body()
{
    timespec tp;
    TimespecTuple tt;

    // Let's do some conclusive subtraction tests
    std::vector<TimespecTuple> subtraction_cases;
    std::vector<TimespecTuple> subtraction_cases_failed;

    // SUBTRACTION CASE 1
    tp.tv_sec  = 0;
    tp.tv_nsec = 0;
    tt.lhs = tp;

    tp.tv_sec  = 0;
    tp.tv_nsec = 1;
    tt.rhs = tp;

    tp.tv_sec  -= 1;
    tp.tv_nsec = 999999999;
    tt.result = tp;

    subtraction_cases.push_back(tt);

    // SUBTRACTION CASE 2
    tp.tv_sec = 2346;
    tp.tv_nsec = 999999999;
    tt.lhs = tp;

    tp.tv_sec = 1000;
    tp.tv_nsec = 40;
    tt.rhs = tp;

    tp.tv_sec = 1346;
    tp.tv_nsec = 999999959;
    tt.result = tp;

    subtraction_cases.push_back(tt);

    // SUBTRACTION CASE 3
    tp.tv_sec = 5;
    tp.tv_nsec = 0;
    tt.lhs = tp;

    tp.tv_sec = 2;
    tp.tv_nsec = 500000000;
    tt.rhs = tp;

    tp.tv_sec = 2;
    tp.tv_nsec = 500000000;
    tt.result = tp;

    subtraction_cases.push_back(tt);

    // SUBTRACTION CASE 4
    tp.tv_sec = 1;
    tp.tv_nsec = 250000000;
    tt.lhs = tp;

    tp.tv_sec = 0;
    tp.tv_nsec = 750000000;
    tt.rhs = tp;

    tp.tv_sec = 0;
    tp.tv_nsec = 500000000;
    tt.result = tp;

    subtraction_cases.push_back(tt);

    for (unsigned int i = 0; i < subtraction_cases.size(); i++)
    {
        PosixTimespec result = PosixTimespec(subtraction_cases[i].lhs) -
            PosixTimespec(subtraction_cases[i].rhs);

        if (result != subtraction_cases[i].result)
        {
            subtraction_cases_failed.push_back(subtraction_cases[i]);
            timespec result_tp;
            result.getTimespec(result_tp);

            std::cout << subtraction_cases[i].lhs.tv_sec << "("
                      << subtraction_cases[i].lhs.tv_nsec << ") - "
                      << subtraction_cases[i].rhs.tv_sec << "("
                      << subtraction_cases[i].rhs.tv_nsec << ") = "
                      << result_tp.tv_sec << "("
                      << result_tp.tv_nsec << "), should be "
                      << subtraction_cases[i].result.tv_sec << "("
                      << subtraction_cases[i].result.tv_nsec << ")\n";
        }
    }

    std::cout << "Failed subtraction cases: " << subtraction_cases_failed.size()
              << "\n";

    MUST_BE_TRUE(subtraction_cases_failed.size() == 0);

    return Test::PASSED;
}

//==============================================================================
Test::Result PosixTimespec_test::Operator::GreaterThan::body()
{
    timespec tp_10;
    timespec tp_01;

    tp_10.tv_sec  = 1;
    tp_10.tv_nsec = 0;

    tp_01.tv_sec  = 0;
    tp_01.tv_nsec = 1;

    MUST_BE_TRUE(PosixTimespec(tp_10) > tp_01 &&
                 tp_10 > PosixTimespec(tp_01) &&
                 PosixTimespec(tp_10) > PosixTimespec(tp_01) &&

                 !(PosixTimespec(tp_10) > tp_10) &&
                 !(tp_10 > PosixTimespec(tp_10)) &&
                 !(PosixTimespec(tp_10) > PosixTimespec(tp_10)) &&

                 !(PosixTimespec(tp_01) > tp_10) &&
                 !(tp_01 > PosixTimespec(tp_10)) &&
                 !(PosixTimespec(tp_01) > PosixTimespec(tp_10)));

    return Test::PASSED;
}

//==============================================================================
Test::Result PosixTimespec_test::Operator::GreaterThanEqualTo::body()
{
    timespec tp_10;
    timespec tp_01;

    tp_10.tv_sec  = 1;
    tp_10.tv_nsec = 0;

    tp_01.tv_sec  = 0;
    tp_01.tv_nsec = 1;

    MUST_BE_TRUE(PosixTimespec(tp_10) >= tp_01 &&
                 tp_10 >= PosixTimespec(tp_01) &&
                 PosixTimespec(tp_10) >= PosixTimespec(tp_01) &&

                 PosixTimespec(tp_10) >= tp_10 &&
                 tp_10 >= PosixTimespec(tp_10) &&
                 PosixTimespec(tp_10) >= PosixTimespec(tp_10) &&

                 !(PosixTimespec(tp_01) >= tp_10) &&
                 !(tp_01 >= PosixTimespec(tp_10)) &&
                 !(PosixTimespec(tp_01) >= PosixTimespec(tp_10)));

    return Test::PASSED;
}

//==============================================================================
Test::Result PosixTimespec_test::Operator::LessThan::body()
{
    timespec tp_10;
    timespec tp_01;

    tp_10.tv_sec  = 1;
    tp_10.tv_nsec = 0;

    tp_01.tv_sec  = 0;
    tp_01.tv_nsec = 1;

    MUST_BE_TRUE(!(PosixTimespec(tp_10) < tp_01) &&
                 !(tp_10 < PosixTimespec(tp_01)) &&
                 !(PosixTimespec(tp_10) < PosixTimespec(tp_01)) &&

                 !(PosixTimespec(tp_10) < tp_10) &&
                 !(tp_10 < PosixTimespec(tp_10)) &&
                 !(PosixTimespec(tp_10) < PosixTimespec(tp_10)) &&

                 PosixTimespec(tp_01) < tp_10 &&
                 tp_01 < PosixTimespec(tp_10) &&
                 PosixTimespec(tp_01) < PosixTimespec(tp_10));

    return Test::PASSED;
}

//==============================================================================
Test::Result PosixTimespec_test::Operator::LessThanEqualTo::body()
{
    timespec tp_10;
    timespec tp_01;

    tp_10.tv_sec  = 1;
    tp_10.tv_nsec = 0;

    tp_01.tv_sec  = 0;
    tp_01.tv_nsec = 1;

    MUST_BE_TRUE(!(PosixTimespec(tp_10) <= tp_01) &&
                 !(tp_10 <= PosixTimespec(tp_01)) &&
                 !(PosixTimespec(tp_10) <= PosixTimespec(tp_01)) &&

                 PosixTimespec(tp_10) <= tp_10 &&
                 tp_10 <= PosixTimespec(tp_10) &&
                 PosixTimespec(tp_10) <= PosixTimespec(tp_10) &&

                 PosixTimespec(tp_01) <= tp_10 &&
                 tp_01 <= PosixTimespec(tp_10) &&
                 PosixTimespec(tp_01) <= PosixTimespec(tp_10));

    return Test::PASSED;
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
