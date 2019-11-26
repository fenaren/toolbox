#include "DisjointSet_test.hpp"

#include "DisjointSet.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(DisjointSet_test);

//==============================================================================
void DisjointSet_test::addTestCases()
{
    ADD_TEST_CASE(Stub);
}

//==============================================================================
Test::Result DisjointSet_test::Stub::body()
{
    DisjointSet<int> disjoint_set;
    return Test::PASSED;
}
