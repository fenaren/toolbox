#include <list>
#include <string>

#include "ConfigurationParameter.hpp"

//=============================================================================================
template <class T> Configuration::Parameter<T>::Parameter(const T& initial_value) :
    ParameterBase(),
    value(initial_value)
{
}

//=============================================================================================
template <class T> Configuration::Parameter<T>::Parameter(const Parameter<T>& parameter) :
    ParameterBase()
{
    parameter.getValue(value);
}

//=============================================================================================
template <class T> Configuration::Parameter<T>::~Parameter()
{
}

//=============================================================================================
template <class T> Configuration::Parameter<T>::operator T() const
{
    return value;
}

//=============================================================================================
template <class T> void Configuration::Parameter<T>::setValue(const T& value)
{
    this->value = value;
    set = true;
}

//=============================================================================================
template <class T> T Configuration::Parameter<T>::getValue() const
{
    return value;
}

//=============================================================================================
template <class T> void Configuration::Parameter<T>::getValue(T& value) const
{
    value = this->value;
}

//=============================================================================================
template <class T>
Configuration::Parameter<T>& Configuration::Parameter<T>::operator=(const Parameter& parameter)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &parameter)
    {
        value = parameter.value;
        set = true;
    }

    return *this;
}

//=============================================================================================
template <class T>
Configuration::Parameter<T>& Configuration::Parameter<T>::operator=(const T& value)
{
    this->value = value;
    set = true;

    return *this;
}

//=============================================================================================
template <class T> bool operator<(const Configuration::Parameter<T>& lhs,
                                  const Configuration::Parameter<T>& rhs)
{
    T lhs_value;
    T rhs_value;

    lhs.getValue(lhs_value);
    rhs.getValue(rhs_value);

    return lhs_value < rhs_value;
}

//=============================================================================================
template <class T> bool operator>(const Configuration::Parameter<T>& lhs,
                                  const Configuration::Parameter<T>& rhs)
{
    return rhs < lhs;
}

//=============================================================================================
template <class T> bool operator<=(const Configuration::Parameter<T>& lhs,
                                   const Configuration::Parameter<T>& rhs)
{
    return !(lhs > rhs);
}

//=============================================================================================
template <class T> bool operator>=(const Configuration::Parameter<T>& lhs,
                                   const Configuration::Parameter<T>& rhs)
{
    return !(lhs < rhs);
}

//=============================================================================================
template <class T> bool operator==(const Configuration::Parameter<T>& lhs,
                                   const Configuration::Parameter<T>& rhs)
{
    T lhs_value;
    T rhs_value;

    lhs.getValue(lhs_value);
    rhs.getValue(rhs_value);

    return lhs_value == rhs_value;
}

//=============================================================================================
template <class T> bool operator!=(const Configuration::Parameter<T>& lhs,
                                   const Configuration::Parameter<T>& rhs)
{
    return !(lhs == rhs);
}

// Defining these operators is a little interesting. To make the operator comparison we have to
// change the type of one of the operators to the type of the other, but changing to the
// non-parameter type to the parameter type isn't an option, because we only know its abstract
// type here.  We have to get its value and then compare non-parameter types.

#define DEFINE_MIXED_PARAMETER_OPERATOR(OPERATOR, OP)                   \
    template <class T> bool OPERATOR(const Configuration::Parameter<T>& lhs, \
                                     const T&                           rhs) \
    {                                                                   \
        T lhs_value;                                                    \
        lhs.getValue(lhs_value);                                        \
        return lhs_value OP rhs;                                        \
    }                                                                   \
                                                                        \
    template <class T> bool OPERATOR(const T&                           lhs, \
                                     const Configuration::Parameter<T>& rhs) \
    {                                                                   \
    T rhs_value;                                                        \
    rhs.getValue(rhs_value);                                            \
    return lhs OP rhs_value;                                            \
    }                                                                   \
                                                                        \
    bool OPERATOR(const Configuration::Parameter<std::string>& lhs, const char* rhs) \
    {                                                                   \
        std::string lhs_value;                                          \
        lhs.getValue(lhs_value);                                        \
        return lhs_value OP rhs;                                        \
    }                                                                   \
                                                                        \
    bool OPERATOR(const char* lhs, const Configuration::Parameter<std::string>& rhs) \
    {                                                                   \
    std::string rhs_value;                                              \
    rhs.getValue(rhs_value);                                            \
    return lhs OP rhs_value;                                            \
    }

DEFINE_MIXED_PARAMETER_OPERATOR(operator<, <);
DEFINE_MIXED_PARAMETER_OPERATOR(operator>, >);
DEFINE_MIXED_PARAMETER_OPERATOR(operator<=, <=);
DEFINE_MIXED_PARAMETER_OPERATOR(operator>=, >=);
DEFINE_MIXED_PARAMETER_OPERATOR(operator==, ==);
DEFINE_MIXED_PARAMETER_OPERATOR(operator!=, !=);

#define INSTANTIATE_PARAMETER_OPERATOR(OPERATOR)                        \
    template bool OPERATOR(const Configuration::Parameter<std::string>&, \
                           const Configuration::Parameter<std::string>&); \
    template bool OPERATOR(const Configuration::Parameter<std::string>&, \
                           const std::string&);                         \
    template bool OPERATOR(const std::string&,                          \
                           const Configuration::Parameter<std::string>&); \
                                                                        \
    template bool OPERATOR(const Configuration::Parameter<bool>&,       \
                           const Configuration::Parameter<bool>&);      \
    template bool OPERATOR(const Configuration::Parameter<bool>&, const bool&); \
    template bool OPERATOR(const bool&, const Configuration::Parameter<bool>&); \
                                                                        \
    template bool OPERATOR(const Configuration::Parameter<char>&,       \
                           const Configuration::Parameter<char>&);      \
    template bool OPERATOR(const Configuration::Parameter<char>&, const char&); \
    template bool OPERATOR(const char&, const Configuration::Parameter<char>&); \
                                                                        \
    template bool OPERATOR(const Configuration::Parameter<double>&,     \
                           const Configuration::Parameter<double>&);    \
    template bool OPERATOR(const Configuration::Parameter<double>&, const double&); \
    template bool OPERATOR(const double&, const Configuration::Parameter<double>&); \
                                                                        \
    template bool OPERATOR(const Configuration::Parameter<float>&,      \
                           const Configuration::Parameter<float>&);     \
    template bool OPERATOR(const Configuration::Parameter<float>&, const float&); \
    template bool OPERATOR(const float&, const Configuration::Parameter<float>&); \
                                                                        \
    template bool OPERATOR(const Configuration::Parameter<int>&,        \
                           const Configuration::Parameter<int>&);       \
    template bool OPERATOR(const Configuration::Parameter<int>&, const int&); \
    template bool OPERATOR(const int&, const Configuration::Parameter<int>&); \
                                                                        \
    template bool OPERATOR(const Configuration::Parameter<long>&,       \
                           const Configuration::Parameter<long>&);      \
    template bool OPERATOR(const Configuration::Parameter<long>&, const long&); \
    template bool OPERATOR(const long&, const Configuration::Parameter<long>&); \
                                                                        \
    template bool OPERATOR(const Configuration::Parameter<long double>&, \
                           const Configuration::Parameter<long double>&); \
    template bool OPERATOR(const Configuration::Parameter<long double>&, \
                           const long double&);                         \
    template bool OPERATOR(const long double&,                          \
                           const Configuration::Parameter<long double>&); \
                                                                        \
    template bool OPERATOR(const Configuration::Parameter<long long>&,  \
                           const Configuration::Parameter<long long>&); \
    template bool OPERATOR(const Configuration::Parameter<long long>&,  \
                           const long long&);                           \
    template bool OPERATOR(const long long&,                            \
                           const Configuration::Parameter<long long>&); \
                                                                        \
    template bool OPERATOR(const Configuration::Parameter<short>&,      \
                           const Configuration::Parameter<short>&);     \
    template bool OPERATOR(const Configuration::Parameter<short>&, const short&); \
    template bool OPERATOR(const short&, const Configuration::Parameter<short>&); \
                                                                        \
    template bool OPERATOR(const Configuration::Parameter<unsigned char>&, \
                           const Configuration::Parameter<unsigned char>&); \
    template bool OPERATOR(const Configuration::Parameter<unsigned char>&, \
                           const unsigned char&);                       \
    template bool OPERATOR(const unsigned char&,                        \
                           const Configuration::Parameter<unsigned char>&); \
                                                                        \
    template bool OPERATOR(const Configuration::Parameter<unsigned int>&, \
                           const Configuration::Parameter<unsigned int>&); \
    template bool OPERATOR(const Configuration::Parameter<unsigned int>&, \
                           const unsigned int&);                        \
    template bool OPERATOR(const unsigned int&,                         \
                           const Configuration::Parameter<unsigned int>&); \
                                                                        \
    template bool OPERATOR(const Configuration::Parameter<unsigned long>&, \
                           const Configuration::Parameter<unsigned long>&); \
    template bool OPERATOR(const Configuration::Parameter<unsigned long>&, \
                           const unsigned long&);                       \
    template bool OPERATOR(const unsigned long&,                        \
                           const Configuration::Parameter<unsigned long>&); \
                                                                        \
    template bool OPERATOR(const Configuration::Parameter<unsigned long long>&, \
                           const Configuration::Parameter<unsigned long long>&); \
    template bool OPERATOR(const Configuration::Parameter<unsigned long long>&, \
                           const unsigned long long&);                  \
    template bool OPERATOR(const unsigned long long&,                   \
                           const Configuration::Parameter<unsigned long long>&); \
                                                                        \
    template bool OPERATOR(const Configuration::Parameter<unsigned short>&, \
                           const Configuration::Parameter<unsigned short>&); \
    template bool OPERATOR(const Configuration::Parameter<unsigned short>&, \
                           const unsigned short&);                      \
    template bool OPERATOR(const unsigned short&,                       \
                           const Configuration::Parameter<unsigned short>&);

INSTANTIATE_PARAMETER_OPERATOR(operator<);
INSTANTIATE_PARAMETER_OPERATOR(operator>);
INSTANTIATE_PARAMETER_OPERATOR(operator<=);
INSTANTIATE_PARAMETER_OPERATOR(operator>=);
INSTANTIATE_PARAMETER_OPERATOR(operator==);
INSTANTIATE_PARAMETER_OPERATOR(operator!=);

namespace Configuration
{
    // Intrinsic types
    template class Parameter<bool>;
    template class Parameter<char>;
    template class Parameter<double>;
    template class Parameter<float>;
    template class Parameter<int>;
    template class Parameter<long>;
    template class Parameter<long double>;
    template class Parameter<long long>;
    template class Parameter<short>;
    template class Parameter<unsigned char>;
    template class Parameter<unsigned int>;
    template class Parameter<unsigned long>;
    template class Parameter<unsigned long long>;
    template class Parameter<unsigned short>;

    template class Parameter<std::string>;

    template class Parameter<std::list<char> >;
    template class Parameter<std::list<double> >;
    template class Parameter<std::list<float> >;
    template class Parameter<std::list<int> >;
    template class Parameter<std::list<long> >;
    template class Parameter<std::list<long double> >;
    template class Parameter<std::list<long long> >;
    template class Parameter<std::list<short> >;
    template class Parameter<std::list<unsigned char> >;
    template class Parameter<std::list<unsigned int> >;
    template class Parameter<std::list<unsigned long> >;
    template class Parameter<std::list<unsigned long long> >;
    template class Parameter<std::list<unsigned short> >;

    template class Parameter<std::list<std::string> >;
}
