#if !defined DISJOINT_SET_TEST_HPP
#define DISJOINT_SET_TEST_HPP

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(DisjointSet_test)

    TEST_CASES_BEGIN(UnionSets)

        TEST(Case1)

    TEST_CASES_END(UnionSets)

    TEST_CASES_BEGIN(IsRepresentative)

        TEST(Case1)
        TEST(Case2)

    TEST_CASES_END(IsRepresentative)

TEST_CASES_END(DisjointSet_test)

#endif
