#include "ArgumentValueList.hpp"

//==============================================================================
template <class T> ArgumentValueList<T>::ArgumentValueList()
{
}

//==============================================================================
template <class T> ArgumentValueList<T>::~ArgumentValueList()
{
}

//==============================================================================
template <class T> ArgumentValueList<T>&
ArgumentValueList<T>::operator=(const ArgumentValueList& argument_value_list)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &argument_value_list)
    {
        // Do something
    }

    return *this;
}
