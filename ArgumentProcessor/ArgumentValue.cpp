#include <sstream>
#include <stdexcept>
#include <string>

#include "ArgumentValue.hpp"

#include "Argument.hpp"

#define DEFINE_OPERATOR_MIXEDTYPES(OPERATOR, OP)        \
    template <class T>                                  \
    bool OPERATOR(const ArgumentValue<T>& lhs, T rhs)   \
    {                                                   \
        return lhs OP ArgumentValue<T>(rhs);            \
    }                                                   \
                                                        \
    template <class T>                                  \
    bool OPERATOR(T lhs, const ArgumentValue<T>& rhs)   \
    {                                                   \
        return ArgumentValue<T>(lhs) OP rhs;            \
    }

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
    T lhs_value;
    T rhs_value;

    lhs.getValue(lhs_value);
    rhs.getValue(rhs_value);

    return lhs_value < rhs_value;
}

DEFINE_OPERATOR_MIXEDTYPES(operator<, <);

//==============================================================================
template <class T>
bool operator>(const ArgumentValue<T>& lhs, const ArgumentValue<T>& rhs)
{
    return rhs < lhs;
}

DEFINE_OPERATOR_MIXEDTYPES(operator>, >);

//==============================================================================
template <class T>
bool operator<=(const ArgumentValue<T>& lhs, const ArgumentValue<T>& rhs)
{
    return !(lhs > rhs);
}

DEFINE_OPERATOR_MIXEDTYPES(operator<=, <=);

//==============================================================================
template <class T>
bool operator>=(const ArgumentValue<T>& lhs, const ArgumentValue<T>& rhs)
{
    return !(lhs < rhs);
}

DEFINE_OPERATOR_MIXEDTYPES(operator>=, >=);

//==============================================================================
template <class T>
bool operator==(const ArgumentValue<T>& lhs, const ArgumentValue<T>& rhs)
{
    T lhs_value;
    T rhs_value;

    lhs.getValue(lhs_value);
    rhs.getValue(rhs_value);

    return lhs_value == rhs_value;
}

DEFINE_OPERATOR_MIXEDTYPES(operator==, ==);

//==============================================================================
template <class T>
bool operator!=(const ArgumentValue<T>& lhs, const ArgumentValue<T>& rhs)
{
    return !(lhs == rhs);
}

DEFINE_OPERATOR_MIXEDTYPES(operator!=, !=);

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

#define INSTANTIATE_RELATIONAL_OPERATOR(OPERATOR)                       \
    template bool OPERATOR(const ArgumentValue<std::string>&,           \
                           const ArgumentValue<std::string>&);          \
    template bool OPERATOR(const ArgumentValue<std::string>&,           \
                           const std::string&);                         \
    template bool OPERATOR(const std::string&,                          \
                           const ArgumentValue<std::string>&);          \
                                                                        \
    template bool OPERATOR(const ArgumentValue<char>&,                  \
                           const ArgumentValue<char>&);                 \
    template bool OPERATOR(const ArgumentValue<char>&, char);           \
    template bool OPERATOR(char, const ArgumentValue<char>&);           \
                                                                        \
    template bool OPERATOR(const ArgumentValue<double>&,                \
                           const ArgumentValue<double>&);               \
    template bool OPERATOR(const ArgumentValue<double>&, double);       \
    template bool OPERATOR(double, const ArgumentValue<double>&);       \
                                                                        \
    template bool OPERATOR(const ArgumentValue<float>&,                 \
                           const ArgumentValue<float>&);                \
    template bool OPERATOR(const ArgumentValue<float>&, float);         \
    template bool OPERATOR(float, const ArgumentValue<float>&);         \
                                                                        \
    template bool OPERATOR(const ArgumentValue<int>&,                   \
                           const ArgumentValue<int>&);                  \
    template bool OPERATOR(const ArgumentValue<int>&, int);             \
    template bool OPERATOR(int, const ArgumentValue<int>&);             \
                                                                        \
    template bool OPERATOR(const ArgumentValue<long>&,                  \
                           const ArgumentValue<long>&);                 \
    template bool OPERATOR(const ArgumentValue<long>&, long);           \
    template bool OPERATOR(long, const ArgumentValue<long>&);           \
                                                                        \
    template bool OPERATOR(const ArgumentValue<long double>&,           \
                           const ArgumentValue<long double>&);          \
    template bool OPERATOR(const ArgumentValue<long double>&, long double); \
    template bool OPERATOR(long double, const ArgumentValue<long double>&); \
                                                                        \
    template bool OPERATOR(const ArgumentValue<long long>&,             \
                           const ArgumentValue<long long>&);            \
    template bool OPERATOR(const ArgumentValue<long long>&, long long); \
    template bool OPERATOR(long long, const ArgumentValue<long long>&); \
                                                                        \
    template bool OPERATOR(const ArgumentValue<short>&,                 \
                           const ArgumentValue<short>&);                \
    template bool OPERATOR(const ArgumentValue<short>&, short);         \
    template bool OPERATOR(short, const ArgumentValue<short>&);         \
                                                                        \
    template bool OPERATOR(const ArgumentValue<unsigned char>&,         \
                           const ArgumentValue<unsigned char>&);        \
    template bool OPERATOR(const ArgumentValue<unsigned char>&,         \
                           unsigned char);                              \
    template bool OPERATOR(unsigned char,                               \
                           const ArgumentValue<unsigned char>&);        \
                                                                        \
    template bool OPERATOR(const ArgumentValue<unsigned int>&,          \
                           const ArgumentValue<unsigned int>&);         \
    template bool OPERATOR(const ArgumentValue<unsigned int>&, unsigned int); \
    template bool OPERATOR(unsigned int, const ArgumentValue<unsigned int>&); \
                                                                        \
    template bool OPERATOR(const ArgumentValue<unsigned long>&,         \
                           const ArgumentValue<unsigned long>&);        \
    template bool OPERATOR(const ArgumentValue<unsigned long>&,         \
                           unsigned long);                              \
    template bool OPERATOR(unsigned long,                               \
                           const ArgumentValue<unsigned long>&);        \
                                                                        \
    template bool OPERATOR(const ArgumentValue<unsigned long long>&,    \
                           const ArgumentValue<unsigned long long>&);   \
    template bool OPERATOR(const ArgumentValue<unsigned long long>&,    \
                           unsigned long long);                         \
    template bool OPERATOR(unsigned long long,                          \
                           const ArgumentValue<unsigned long long>&);   \
                                                                        \
    template bool OPERATOR(const ArgumentValue<unsigned short>&,        \
                           const ArgumentValue<unsigned short>&);       \
    template bool OPERATOR(const ArgumentValue<unsigned short>&,        \
                           unsigned short);                             \
    template bool OPERATOR(unsigned short,                              \
                           const ArgumentValue<unsigned short>&);

INSTANTIATE_RELATIONAL_OPERATOR(operator<)
INSTANTIATE_RELATIONAL_OPERATOR(operator>)
INSTANTIATE_RELATIONAL_OPERATOR(operator<=)
INSTANTIATE_RELATIONAL_OPERATOR(operator>=)
INSTANTIATE_RELATIONAL_OPERATOR(operator==)
INSTANTIATE_RELATIONAL_OPERATOR(operator!=)
