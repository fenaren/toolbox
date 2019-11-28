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
    ADD_TEST_CASE(MakeSet);
    ADD_TEST_CASE(Find);
    ADD_TEST_CASE(UnionSets);
    ADD_TEST_CASE(IsRepresentative);
}

//==============================================================================
Test::Result DisjointSet_test::MakeSet::body()
{
    DisjointSet<int> disjoint_set;

    int a = 1;
    int b = 2;
    int c = 3;

    disjoint_set.makeSet(&a);
    disjoint_set.makeSet(&b);
    disjoint_set.makeSet(&c);

    // We made three single-element disjoint sets so there should be three
    // tracked.
    MUST_BE_TRUE(disjoint_set.elements_map.size() == 3);

    // We should be able to find DisjointSetElements for all three elements, and
    // they should all be their own parents.

    MUST_BE_TRUE(disjoint_set.elements_map[&a].getParent() ==
                 &disjoint_set.elements_map[&a]);

    MUST_BE_TRUE(disjoint_set.elements_map[&b].getParent() ==
                 &disjoint_set.elements_map[&b]);

    MUST_BE_TRUE(disjoint_set.elements_map[&c].getParent() ==
                 &disjoint_set.elements_map[&c]);

    return Test::PASSED;
}

//==============================================================================
Test::Result DisjointSet_test::Find::body()
{
    return Test::PASSED;
}

//==============================================================================
Test::Result DisjointSet_test::UnionSets::body()
{
    DisjointSet<int> disjoint_set;

    int a = 1;
    int b = 2;
    int c = 3;

    disjoint_set.makeSet(&a);
    disjoint_set.makeSet(&b);
    disjoint_set.makeSet(&c);

    disjoint_set.unionSets(&a, &b);

    DisjointSetElement<int>* element_a = &disjoint_set.elements_map[&a];
    DisjointSetElement<int>* element_b = &disjoint_set.elements_map[&b];
    DisjointSetElement<int>* element_c = &disjoint_set.elements_map[&c];

    // Either a or b must be the parent of both.  It doesn't matter which is the
    // parent, both situations are acceptable for correct functionality.
    MUST_BE_TRUE((element_a->getParent() == element_b &&
                  element_b->getParent() == element_b) ||
                 (element_a->getParent() == element_a &&
                  element_b->getParent() == element_a));

    // We didn't touch this one so it should still refer to itself.
    MUST_BE_TRUE(element_c->getParent() == element_c);

    return Test::PASSED;
 }

//==============================================================================
Test::Result DisjointSet_test::IsRepresentative::body()
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
