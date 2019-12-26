#include <sstream>
#include <string>

#include "ArgumentValueList.hpp"

//==============================================================================
template <class T> ArgumentValueList<T>::ArgumentValueList() :
    Argument()
{
}

//==============================================================================
template <class T> ArgumentValueList<T>::~ArgumentValueList()
{
}

//==============================================================================
template <class T> void ArgumentValueList<T>::update(const std::string& value)
{
    std::istringstream converter(value);
    T new_value;
    converter >> new_value;

    // Did the conversion go okay?
    if (!converter)
    {
        throw std::runtime_error("Error converting value to template type");
    }

    values.push_back(new_value);
    set();
}

//==============================================================================
template <class T> ArgumentValueList<T>& ArgumentValueList<T>::operator=(
    const ArgumentValueList<T>& argument_value_list)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &argument_value_list)
    {
        // Do something
    }

    return *this;
}

template class ArgumentValueList<std::string>;

template class ArgumentValueList<char>;
template class ArgumentValueList<double>;
template class ArgumentValueList<float>;
template class ArgumentValueList<int>;
template class ArgumentValueList<long>;
template class ArgumentValueList<long double>;
template class ArgumentValueList<long long>;
template class ArgumentValueList<short>;
template class ArgumentValueList<unsigned char>;
template class ArgumentValueList<unsigned int>;
template class ArgumentValueList<unsigned long>;
template class ArgumentValueList<unsigned long long>;
template class ArgumentValueList<unsigned short>;
