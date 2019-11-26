#include "DisjointSet_test.hpp"

#include "DisjointSet.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(DisjointSet_test);

//==============================================================================
void DisjointSet_test::addTestCases()
{
    ADD_TEST_CASE(IsRepresentative);
}

//==============================================================================
Test::Result DisjointSet_test::IsRepresentative::body()
{
    // We'll track these three.
    int a = 1;
    int b = 2;
    int c = 3;

    DisjointSet<int> disjoint_set;

    disjoint_set.makeSet(&a);
    disjoint_set.makeSet(&b);
    disjoint_set.makeSet(&c);

    return Test::PASSED;
}
