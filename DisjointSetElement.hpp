#if !defined DISJOINT_SET_ELEMENT_HPP
#define DISJOINT_SET_ELEMENT_HPP

template <class T> class DisjointSetElement
{
public:

    // Initializes data members, nothing more.
    DisjointSetElement(const T*               element,
                       DisjointSetElement<T>* parent = 0);

    // Does nothing.
    ~DisjointSetElement();

private:

    // The thing we're actually tracking
    const T* element;

    // Follow this to get to the representative
    DisjointSetElement<T>* parent;

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    DisjointSetElement(const DisjointSetElement&);
    DisjointSetElement& operator=(const DisjointSetElement&);
};

#endif
