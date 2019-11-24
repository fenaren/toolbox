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
