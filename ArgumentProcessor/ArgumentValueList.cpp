#include <list>
#include <sstream>
#include <string>

#include "ArgumentValueList.hpp"

//==============================================================================
template <class T>
ArgumentValueList<T>::ArgumentValueList(const std::list<T>& default_values) :
    Argument(),
    values(default_values)
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
        values = argument_value_list.values;
    }

    return *this;
}

//==============================================================================
template <class T> bool operator==(const ArgumentValueList<T>& lhs,
                                   const ArgumentValueList<T>& rhs)
{
    std::list<T> lhs_values;
    std::list<T> rhs_values;

    lhs.getValues(lhs_values);
    rhs.getValues(rhs_values);

    return lhs_values == rhs_values;
}

//==============================================================================
template <class T> bool operator!=(const ArgumentValueList<T>& lhs,
                                   const ArgumentValueList<T>& rhs)
{
    return !(lhs == rhs);
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
