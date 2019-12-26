#include <sstream>
#include <stdexcept>
#include <string>

#include "ArgumentValue.hpp"

#include "Argument.hpp"

//==============================================================================
template <class T> ArgumentValue<T>::ArgumentValue(const T& default_value) :
    Argument(),
    value(default_value)
{
}

//==============================================================================
template <class T> ArgumentValue<T>::~ArgumentValue()
{
}

//==============================================================================
template <class T> void ArgumentValue<T>::update(const std::string& value)
{
    std::istringstream converter(value);
    converter >> this->value;

    // Did the conversion go okay?
    if (!converter)
    {
        throw std::runtime_error("Error converting value to template type");
    }

    set();
}

//==============================================================================
template <class T> T ArgumentValue<T>::getValue() const
{
    return value;
}

//==============================================================================
template <class T> void ArgumentValue<T>::getValue(T& value) const
{
    value = this->value;
}

//==============================================================================
template <class T> ArgumentValue<T>&
ArgumentValue<T>::operator=(const ArgumentValue& argument_value)
{
    Argument::operator=(argument_value);

    // Don't do anything if we're assigning to ourselves
    if (this != &argument_value)
    {
        value = argument_value.value;
    }

    return *this;
}

//==============================================================================
template <class T> ArgumentValue<T>& ArgumentValue<T>::operator=(const T& value)
{
    this->value = value;
    set();

    return *this;
}

//==============================================================================
template <class T>
bool operator<(const ArgumentValue<T>& lhs, const ArgumentValue<T>& rhs)
{
    if (!lhs.isSet() || !rhs.isSet())
    {
        throw std::runtime_error("Both sides (lhs and rhs) must be set");
    }

    T lhs_value;
    T rhs_value;

    lhs.getValue(lhs_value);
    rhs.getValue(rhs_value);

    return lhs_value < rhs_value;
}

//==============================================================================
template <class T>
bool operator>(const ArgumentValue<T>& lhs, const ArgumentValue<T>& rhs)
{
    return rhs < lhs;
}

//==============================================================================
template <class T>
bool operator<=(const ArgumentValue<T>& lhs, const ArgumentValue<T>& rhs)
{
    return !(lhs > rhs);
}

//==============================================================================
template <class T>
bool operator>=(const ArgumentValue<T>& lhs, const ArgumentValue<T>& rhs)
{
    return !(lhs < rhs);
}

//==============================================================================
template <class T>
bool operator==(const ArgumentValue<T>& lhs, const ArgumentValue<T>& rhs)
{
    if (!lhs.isSet() || !rhs.isSet())
    {
        throw std::runtime_error("Both sides (lhs and rhs) must be set");
    }

    T lhs_value;
    T rhs_value;

    lhs.getValue(lhs_value);
    rhs.getValue(rhs_value);

    return lhs_value == rhs_value;
}

//==============================================================================
template <class T>
bool operator!=(const ArgumentValue<T>& lhs, const ArgumentValue<T>& rhs)
{
    return !(lhs == rhs);
}

template class ArgumentValue<std::string>;

template class ArgumentValue<char>;
template class ArgumentValue<double>;
template class ArgumentValue<float>;
template class ArgumentValue<int>;
template class ArgumentValue<long>;
template class ArgumentValue<long double>;
template class ArgumentValue<long long>;
template class ArgumentValue<short>;
template class ArgumentValue<unsigned char>;
template class ArgumentValue<unsigned int>;
template class ArgumentValue<unsigned long>;
template class ArgumentValue<unsigned long long>;
template class ArgumentValue<unsigned short>;
