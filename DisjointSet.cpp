#include <stdexcept>

#include "DisjointSet.hpp"

#include "DisjointSetElement.hpp"

//==============================================================================
template <class T> DisjointSet<T>::DisjointSet()
{
}

//==============================================================================
template <class T>
DisjointSet<T>::DisjointSet(const DisjointSet<T>& disjoint_set)
{
    *this = disjoint_set;
}

//==============================================================================
template <class T> DisjointSet<T>::~DisjointSet()
{
}

//==============================================================================
template <class T> void DisjointSet<T>::makeSet(T* element)
{
    // Make sure we're not already tracking this element.
    if (elements_map.find(element) != elements_map.end())
    {
        throw std::runtime_error("Element is already in at least one set");
        return;
    }

    // Keep track of this new element.  We can't have the DisjointSetElement set
    // itself as its own parent here, because at the DisjointSetElement always
    // has the same memory address here.
    elements_map[element] = DisjointSetElement<T>(element);

    // Set the new element as its own parent after it's been copied into the
    // map, ensuring it has the right parent pointer.
    elements_map[element].setParent(&elements_map[element]);
}

//==============================================================================
template <class T> T* DisjointSet<T>::find(T* element)
{
    // Why is "typename" needed here?
    typename std::map<T*, DisjointSetElement<T> >::iterator dj_element =
        elements_map.find(element);

    if (dj_element == elements_map.end())
    {
        throw std::runtime_error("Element is not in any set");

        // We have nothing useful to return here.
        return 0;
    }

    // Find the representative.  This is the part that scales poorly without
    // path compression.
    DisjointSetElement<T>* representative = &dj_element->second;
    while (representative->getParent() != representative)
    {
        representative = representative->getParent();
    }

    return representative->getElement();
}

//==============================================================================
template <class T> void DisjointSet<T>::unionSets(T* element1, T* element2)
{
    T* rep_element1 = find(element1);
    T* rep_element2 = find(element2);

    // These elements will have the same representative if they are already in
    // the same set.
    if (rep_element1 == rep_element2)
    {
        return;
    }

    elements_map[rep_element1].setParent(&elements_map[rep_element2]);
}

//==============================================================================
template <class T> bool DisjointSet<T>::isRepresentative(T* element)
{
    // Finds on the representative element of a set return the representative.
    return element == find(element);
}

//==============================================================================
template <class T> void DisjointSet<T>::getElementsMap(
    std::map<T*, DisjointSetElement<T> >& elements_map) const
{
    elements_map = this->elements_map;
}

//==============================================================================
template <class T>
DisjointSet<T>& DisjointSet<T>::operator=(const DisjointSet<T>& disjoint_set)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &disjoint_set)
    {
        disjoint_set.getElementsMap(this->elements_map);
    }

    return *this;
}

template class DisjointSet<char>;
template class DisjointSet<double>;
template class DisjointSet<float>;
template class DisjointSet<int>;
template class DisjointSet<long>;
template class DisjointSet<long double>;
template class DisjointSet<long long>;
template class DisjointSet<short>;
template class DisjointSet<unsigned char>;
template class DisjointSet<unsigned int>;
template class DisjointSet<unsigned long>;
template class DisjointSet<unsigned long long>;
template class DisjointSet<unsigned short>;
