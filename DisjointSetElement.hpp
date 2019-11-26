#if !defined DISJOINT_SET_ELEMENT_HPP
#define DISJOINT_SET_ELEMENT_HPP

template <class T> class DisjointSetElement
{
public:

    // Initializes data members, nothing more.
    DisjointSetElement(T*                     element = 0,
                       DisjointSetElement<T>* parent  = 0);

    DisjointSetElement(const DisjointSetElement& dj_element);

    // Does nothing.
    ~DisjointSetElement();

    T* getElement() const;

    DisjointSetElement<T>* getParent() const;

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
template <class T>
DisjointSetElement<T>* DisjointSetElement<T>::getParent() const
{
    return parent;
}

template <class T> bool operator==(const DisjointSetElement<T>& lhs,
                                   const DisjointSetElement<T>& rhs);

#endif
