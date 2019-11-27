#include <iostream>

#include "DisjointSet_test.hpp"

#include "DisjointSet.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(DisjointSet_test);

//==============================================================================
void DisjointSet_test::addTestCases()
{
    ADD_TEST_CASE(UnionSets);
    ADD_TEST_CASE(IsRepresentative);
}

//==============================================================================
void DisjointSet_test::IsRepresentative::addTestCases()
{
    ADD_TEST_CASE(Case1);
    ADD_TEST_CASE(Case2);
}

//==============================================================================
void DisjointSet_test::UnionSets::addTestCases()
{
    ADD_TEST_CASE(Case1);
}

//==============================================================================
Test::Result DisjointSet_test::UnionSets::Case1::body()
{
    DisjointSet<int> disjoint_set;

    int a = 1;
    int b = 2;
    int c = 3;

    disjoint_set.makeSet(&a);
    disjoint_set.makeSet(&b);
    disjoint_set.makeSet(&c);

    disjoint_set.unionSets(&a, &b);

    DisjointSetElement<int>* element_a = &disjoint_set.dj_elements[&a];
    DisjointSetElement<int>* element_b = &disjoint_set.dj_elements[&b];
    DisjointSetElement<int>* element_c = &disjoint_set.dj_elements[&c];

    MUST_BE_TRUE(element_a->getParent() == element_b ||
                 element_b->getParent() == element_a);

    MUST_BE_TRUE(element_c->getParent() == 0);

    return Test::PASSED;
 }

//==============================================================================
Test::Result DisjointSet_test::IsRepresentative::Case1::body()
{
    DisjointSet<int> disjoint_set;

    int a = 1;
    int b = 2;
    int c = 3;

    disjoint_set.makeSet(&a);
    disjoint_set.makeSet(&b);
    disjoint_set.makeSet(&c);

    MUST_BE_TRUE(disjoint_set.isRepresentative(&a));
    MUST_BE_TRUE(disjoint_set.isRepresentative(&b));
    MUST_BE_TRUE(disjoint_set.isRepresentative(&c));

    return Test::PASSED;
}

//==============================================================================
Test::Result DisjointSet_test::IsRepresentative::Case2::body()
{
    DisjointSet<int> disjoint_set;

    int a = 1;
    int b = 2;
    int c = 3;

    disjoint_set.makeSet(&a);
    disjoint_set.makeSet(&b);
    disjoint_set.makeSet(&c);

    return Test::PASSED;
}
