#if !defined DISJOINT_SET_ELEMENT_HPP
#define DISJOINT_SET_ELEMENT_HPP

template <class T> class DisjointSetElement
{
public:

    // Initializes data members, nothing more.
    DisjointSetElement(T*                     element = 0,
                       DisjointSetElement<T>* parent  = 0);

    // Copy constructor
    DisjointSetElement(const DisjointSetElement& dj_element);

    // Does nothing.
    ~DisjointSetElement();

    // For getting and setting the represented element.
    T* getElement() const;
    void setElement(T* element);

    // For getting and setting parents
    DisjointSetElement<T>* getParent() const;
    void setParent(DisjointSetElement<T>* parent);

    DisjointSetElement& operator=(const DisjointSetElement&);

private:

    // The thing we're actually tracking
    T* element;

    // Follow this to get to the representative
    DisjointSetElement<T>* parent;
};

//==============================================================================
template <class T> T* DisjointSetElement<T>::getElement() const
{
    return element;
}

//==============================================================================
template <class T> void DisjointSetElement<T>::setElement(T* element)
{
    this->element = element;
}

//==============================================================================
template <class T>
DisjointSetElement<T>* DisjointSetElement<T>::getParent() const
{
    return parent;
}

//==============================================================================
template <class T>
void DisjointSetElement<T>::setParent(DisjointSetElement<T>* parent)
{
    this->parent = parent;
}

#endif
