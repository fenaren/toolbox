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
    ADD_TEST_CASE(UnionSetsFind);
    ADD_TEST_CASE(IsRepresentative);
}

//==============================================================================
void DisjointSet_test::UnionSetsFind::addTestCases()
{
    ADD_TEST_CASE(Case1);
    ADD_TEST_CASE(Case2);
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
Test::Result DisjointSet_test::UnionSetsFind::Case1::body()
{
    DisjointSet<int> disjoint_set;

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    disjoint_set.makeSet(&a);
    disjoint_set.makeSet(&b);
    disjoint_set.makeSet(&c);
    disjoint_set.makeSet(&d);

    disjoint_set.unionSets(&a, &b);
    disjoint_set.unionSets(&c, &d);

    DisjointSetElement<int>* element_a = &disjoint_set.elements_map[&a];
    DisjointSetElement<int>* element_b = &disjoint_set.elements_map[&b];
    DisjointSetElement<int>* element_c = &disjoint_set.elements_map[&c];
    DisjointSetElement<int>* element_d = &disjoint_set.elements_map[&d];

    MUST_BE_TRUE(element_a->getParent() == element_b->getParent());
    MUST_BE_TRUE(element_c->getParent() == element_d->getParent());

    MUST_BE_TRUE(element_a->getParent() != element_c->getParent());
    MUST_BE_TRUE(element_b->getParent() != element_d->getParent());

    disjoint_set.unionSets(&a, &c);

    // They're all in the same set now so they should all have the same
    // representative.  I thought about not using the find method here, since
    // I'd like to test unionSets exclusively, but I could only think to avoid
    // using the find method by reimplementing it, which is almost pointless.
    MUST_BE_TRUE(disjoint_set.find(&a) == disjoint_set.find(&b));
    MUST_BE_TRUE(disjoint_set.find(&a) == disjoint_set.find(&c));
    MUST_BE_TRUE(disjoint_set.find(&a) == disjoint_set.find(&d));

    return Test::PASSED;
 }

//==============================================================================
Test::Result DisjointSet_test::UnionSetsFind::Case2::body()
{
    DisjointSet<int> disjoint_set;

    int a = 1;
    int b = 2;
    int c = 3;

    disjoint_set.makeSet(&a);
    disjoint_set.makeSet(&b);
    disjoint_set.makeSet(&c);

    disjoint_set.unionSets(&a, &b);

    MUST_BE_TRUE(disjoint_set.find(&a) == disjoint_set.find(&b));
    MUST_BE_TRUE(disjoint_set.find(&c) == &c);

    disjoint_set.unionSets(&b, &c);

    MUST_BE_TRUE(disjoint_set.find(&a) == disjoint_set.find(&b));
    MUST_BE_TRUE(disjoint_set.find(&a) == disjoint_set.find(&c));

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
