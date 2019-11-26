#include <stdexcept>

#include "DisjointSet.hpp"

//==============================================================================
template <class T> DisjointSet<T>::DisjointSet()
{
}

//==============================================================================
template <class T> DisjointSet<T>::~DisjointSet()
{
}

//==============================================================================
template <class T> void DisjointSet<T>::makeSet(const T* element)
{
    // Make sure we're not already tracking this element.
    if (dj_elements.find(element) != dj_elements.end())
    {
        throw std::runtime_error("Element is already in at least one set");
    }

    // Keep track of this new element
    //dj_elements[element] = 
}

//==============================================================================
template <class T> T* DisjointSet<T>::find(const T* element)
{
    // Why is "typename" needed here?
    typename std::map<const T*, DisjointSetElement<T> >::iterator dj_element =
        dj_elements.find(element);

    if (dj_element == dj_elements.end())
    {
        throw std::runtime_error("Element is not in any set");

        // We have nothing useful to return here.
        return 0;
    }

    // Find the representative.  This is the part that scales poorly without
    // path compression.
    DisjointSetElement<T>* representative = dj_element->second.getParent();
    while (representative != 0 && representative->getParent() != 0)
    {
        representative = representative->getParent();
    }

    return representative->getElement();
}

//==============================================================================
// If implemented, operator= should follow this template
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
