#include "DisjointSetElement.hpp"

//==============================================================================
template <class T> DisjointSetElement<T>::DisjointSetElement(
    T*                     element,
    DisjointSetElement<T>* parent) :
    element(element),
    parent(parent)
{
}

//==============================================================================
template <class T> DisjointSetElement<T>::DisjointSetElement(
    const DisjointSetElement<T>& dj_element)
{
    *this = dj_element;
}

//==============================================================================
template <class T> DisjointSetElement<T>::~DisjointSetElement()
{
}

//==============================================================================
template <class T> DisjointSetElement<T>&
DisjointSetElement<T>::operator=(const DisjointSetElement<T>& template_class)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &template_class)
    {
        this->element = template_class.getElement();
        this->parent  = template_class.getParent();
    }

    return *this;
}

//==============================================================================
template <class T> bool operator==(const DisjointSetElement<T>& lhs,
                                   const DisjointSetElement<T>& rhs)
{
    return lhs.getElement() == rhs.getElement();
}

template class DisjointSetElement<char>;
template class DisjointSetElement<double>;
template class DisjointSetElement<float>;
template class DisjointSetElement<int>;
template class DisjointSetElement<long>;
template class DisjointSetElement<long double>;
template class DisjointSetElement<long long>;
template class DisjointSetElement<short>;
template class DisjointSetElement<unsigned char>;
template class DisjointSetElement<unsigned int>;
template class DisjointSetElement<unsigned long>;
template class DisjointSetElement<unsigned long long>;
template class DisjointSetElement<unsigned short>;
