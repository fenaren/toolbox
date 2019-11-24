#if !defined DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

#include <unordered_set>

template <class T> class DisjointSet
{
public:

    // Frobnicates the widget
    DisjointSet();

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    ~DisjointSet();

    void MakeSet(const T* element);

    T* Find(const T* element);

    void Union(const T* element1, const T* element2);

private:

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    DisjointSet(const DisjointSet&);
    DisjointSet& operator=(const DisjointSet&);
};

#endif
