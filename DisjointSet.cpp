#include <stdexcept>

#include "DisjointSet.hpp"

#include "DisjointSetElement.hpp"

//==============================================================================
template <class T> DisjointSet<T>::DisjointSet()
{
}

//==============================================================================
template <class T> DisjointSet<T>::~DisjointSet()
{
}

//==============================================================================
template <class T> void DisjointSet<T>::makeSet(T* element)
{
    // Make sure we're not already tracking this element.
    if (dj_elements.find(element) != dj_elements.end())
    {
        throw std::runtime_error("Element is already in at least one set");
        return;
    }

    // Keep track of this new element.  It has no parent which implicitly makes
    // it the only element in its set.
    DisjointSetElement<T> asdf(element);
    dj_elements[element] = asdf;
}

//==============================================================================
template <class T> T* DisjointSet<T>::find(T* element)
{
    // Why is "typename" needed here?
    typename std::map<T*, DisjointSetElement<T> >::iterator dj_element =
        dj_elements.find(element);

    if (dj_element == dj_elements.end())
    {
        throw std::runtime_error("Element is not in any set");

        // We have nothing useful to return here.
        return 0;
    }

    // Find the representative.  This is the part that scales poorly without
    // path compression.
    DisjointSetElement<T>* representative = &dj_element->second;
    while (representative->getParent() != 0)
    {
        representative = representative->getParent();
    }

    return representative->getElement();
}

//==============================================================================
template <class T> void DisjointSet<T>::unionSets(T* element1, T* element2)
{
    // These elements will have the same representative if they are already in
    // the same set.

    T* rep_element1 = find(element1);
    T* rep_element2 = find(element2);

    if (rep_element1 == rep_element2)
    {
        return;
    }

    dj_elements[rep_element1].setParent(&dj_elements[rep_element2]);
}

//==============================================================================
template <class T> bool DisjointSet<T>::isRepresentative(T* element)
{
    // Finds on the representative element of a set return the representative.
    return element == find(element);
}

//==============================================================================
template <class T>
DisjointSet<T>& DisjointSet<T>::operator=(const DisjointSet<T>& template_class)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &template_class)
    {
        // Do something
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
