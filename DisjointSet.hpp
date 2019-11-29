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

    // Copy constructor
    DisjointSet(const DisjointSet&);

    // Does nothing.
    ~DisjointSet();

    // Starts tracking whatever is passed in as a new disjointed set (does not
    // belong to any other tracked sets)
    void makeSet(T* element);

    // Unions the two sets given as arguments.  After this they will both belong
    // to the same set.
    void unionSets(T* element1, T* element2);

    // Returns the representative of the set containing the "element" argument
    T* find(T* element);

    // Returns true if the given element is the representative of its set.
    bool isRepresentative(T* element);

    // Allows retrieval of the internal map used to track all known elements
    // regardless of set.  This exists primarily for the assignment operator.
    void
    getElementsMap(std::map<T*, DisjointSetElement<T> >& elements_map) const;

    DisjointSet& operator=(const DisjointSet&);

private:

    // Allows us to get the DisjointSetElement container for a given element.
    // When the user does a union or find we can get into our data structure
    // with this.
    std::map<T*, DisjointSetElement<T> > elements_map;
};

#endif
