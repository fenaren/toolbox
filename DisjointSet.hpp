#if !defined DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

#include <map>

#include "DisjointSetElement.hpp"

// An implememtation of the canonical disjoint sets data structure.  No path
// shortening for now, so lookups may be worst-case linear in the size of the
// set.
template <class T> class DisjointSet
{
public:

    friend class DisjointSet_test;

    // Initializes with no sets tracked
    DisjointSet();

    // Frees any allocated set elements
    ~DisjointSet();

    // Starts tracking whatever is passed in as a new disjointed set (does not
    // belong to any other tracked sets)
    void makeSet(const T* element);

    // Returns the representative of the set containing the "element" argument
    T* find(const T* element);

    // Unions the two sets given as arguments.  After this they will both belong
    // to the same set.
    void unionSets(const T* element1, const T* element2);

    // Returns true if the given element is the representative of its set.
    bool isRepresentative(const T* element);

private:

    // Allows us to get the DisjointSetElement container for a given element.
    // When the user does a union or find we can get into our data structure
    // with this.
    std::map<const T*, DisjointSetElement<T> > dj_elements;

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    DisjointSet(const DisjointSet&);
    DisjointSet& operator=(const DisjointSet&);
};

#endif
