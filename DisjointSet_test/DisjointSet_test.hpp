#if !defined DISJOINT_SET_TEST_HPP
#define DISJOINT_SET_TEST_HPP

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(DisjointSet_test)

    TEST(MakeSet)

    TEST_CASES_BEGIN(UnionSetsFind)

        TEST(Case1)
        TEST(Case2)

    TEST_CASES_END(UnionSetsFind)

    TEST(IsRepresentative)

TEST_CASES_END(DisjointSet_test)

#endif
