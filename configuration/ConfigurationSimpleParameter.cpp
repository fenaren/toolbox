#include <sstream>
#include <string>

#include "ConfigurationSimpleParameter.hpp"

//=============================================================================================
template <class T> Configuration::SimpleParameter<T>::SimpleParameter(const T& initial_value) :
    Parameter(),
    value(initial_value)
{
}

//=============================================================================================
template <class T>
Configuration::SimpleParameter<T>::SimpleParameter(const SimpleParameter<T>& parameter) :
    Parameter()
{
    parameter.getValue(value);
}

//=============================================================================================
template <class T> Configuration::SimpleParameter<T>::~SimpleParameter()
{
}

//=============================================================================================
template <class T> Configuration::SimpleParameter<T>::operator T() const
{
    return value;
}

//=============================================================================================
template <class T> void Configuration::SimpleParameter<T>::setValue(const T& value)
{
    this->value = value;
    set = true;
}

//=============================================================================================
template <class T> T Configuration::SimpleParameter<T>::getValue() const
{
    return value;
}

//=============================================================================================
template <class T> void Configuration::SimpleParameter<T>::getValue(T& value) const
{
    value = this->value;
}

//=============================================================================================
template <class T> void Configuration::SimpleParameter<T>::fromString(const std::string& value)
{
    std::istringstream outstream(value);
    outstream >> this->value;
}

//=============================================================================================
template <class T> void Configuration::SimpleParameter<T>::toString(std::string& value) const
{
    std::ostringstream instream;
    instream << this->value;
    value = instream.str();
}

//=============================================================================================
template <class T> Configuration::SimpleParameter<T>&
Configuration::SimpleParameter<T>::operator=(const SimpleParameter& parameter)
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
template <class T> Configuration::SimpleParameter<T>&
Configuration::SimpleParameter<T>::operator=(const T& value)
{
    this->value = value;
    set = true;

    return *this;
}

//=============================================================================================
template <class T> bool operator<(const Configuration::SimpleParameter<T>& lhs,
                                  const Configuration::SimpleParameter<T>& rhs)
{
    T lhs_value;
    T rhs_value;

    lhs.getValue(lhs_value);
    rhs.getValue(rhs_value);

    return lhs_value < rhs_value;
}

//=============================================================================================
template <class T> bool operator>(const Configuration::SimpleParameter<T>& lhs,
                                  const Configuration::SimpleParameter<T>& rhs)
{
    return rhs < lhs;
}

//=============================================================================================
template <class T> bool operator<=(const Configuration::SimpleParameter<T>& lhs,
                                   const Configuration::SimpleParameter<T>& rhs)
{
    return !(lhs > rhs);
}

//=============================================================================================
template <class T> bool operator>=(const Configuration::SimpleParameter<T>& lhs,
                                   const Configuration::SimpleParameter<T>& rhs)
{
    return !(lhs < rhs);
}

//=============================================================================================
template <class T> bool operator==(const Configuration::SimpleParameter<T>& lhs,
                                   const Configuration::SimpleParameter<T>& rhs)
{
    T lhs_value;
    T rhs_value;

    lhs.getValue(lhs_value);
    rhs.getValue(rhs_value);

    return lhs_value == rhs_value;
}

//=============================================================================================
template <class T> bool operator!=(const Configuration::SimpleParameter<T>& lhs,
                                   const Configuration::SimpleParameter<T>& rhs)
{
    return !(lhs == rhs);
}

#define DEFINE_MIXED_SIMPLE_PARAMETER_OPERATOR(OPERATOR, OP)            \
    template <class T> bool OPERATOR(const Configuration::SimpleParameter<T>& lhs, \
                                     const T& rhs)                      \
    {                                                                   \
        return lhs OP Configuration::SimpleParameter<T>(rhs);           \
    }                                                                   \
                                                                        \
    template <class T> bool OPERATOR(const T& lhs,                      \
                                     const Configuration::SimpleParameter<T>& rhs) \
    {                                                                   \
        return Configuration::SimpleParameter<T>(lhs) OP rhs;           \
    }                                                                   \
                                                                        \
    bool OPERATOR(const Configuration::SimpleParameter<std::string>& lhs, const char* rhs) \
    {                                                                   \
        return lhs OP Configuration::SimpleParameter<std::string>(rhs); \
    }                                                                   \
                                                                        \
    bool OPERATOR(const char* lhs, const Configuration::SimpleParameter<std::string>& rhs) \
    {                                                                   \
        return Configuration::SimpleParameter<std::string>(lhs) OP rhs; \
    }

DEFINE_MIXED_SIMPLE_PARAMETER_OPERATOR(operator<, <);
DEFINE_MIXED_SIMPLE_PARAMETER_OPERATOR(operator>, >);
DEFINE_MIXED_SIMPLE_PARAMETER_OPERATOR(operator<=, <=);
DEFINE_MIXED_SIMPLE_PARAMETER_OPERATOR(operator>=, >=);
DEFINE_MIXED_SIMPLE_PARAMETER_OPERATOR(operator==, ==);
DEFINE_MIXED_SIMPLE_PARAMETER_OPERATOR(operator!=, !=);

#define INSTANTIATE_SIMPLE_PARAMETER_OPERATOR(OPERATOR)                 \
    template bool OPERATOR(const Configuration::SimpleParameter<std::string>&, \
                           const Configuration::SimpleParameter<std::string>&); \
    template bool OPERATOR(const Configuration::SimpleParameter<std::string>&, \
                           const std::string&);                         \
    template bool OPERATOR(const std::string&,                          \
                           const Configuration::SimpleParameter<std::string>&); \
                                                                        \
    template bool OPERATOR(const Configuration::SimpleParameter<char>&, \
                           const Configuration::SimpleParameter<char>&); \
    template bool OPERATOR(const Configuration::SimpleParameter<char>&, const char&); \
    template bool OPERATOR(const char&, const Configuration::SimpleParameter<char>&); \
                                                                        \
    template bool OPERATOR(const Configuration::SimpleParameter<double>&, \
                           const Configuration::SimpleParameter<double>&); \
    template bool OPERATOR(const Configuration::SimpleParameter<double>&, const double&); \
    template bool OPERATOR(const double&, const Configuration::SimpleParameter<double>&); \
                                                                        \
    template bool OPERATOR(const Configuration::SimpleParameter<float>&, \
                           const Configuration::SimpleParameter<float>&); \
    template bool OPERATOR(const Configuration::SimpleParameter<float>&, const float&); \
    template bool OPERATOR(const float&, const Configuration::SimpleParameter<float>&); \
                                                                        \
    template bool OPERATOR(const Configuration::SimpleParameter<int>&,  \
                           const Configuration::SimpleParameter<int>&); \
    template bool OPERATOR(const Configuration::SimpleParameter<int>&, const int&); \
    template bool OPERATOR(const int&, const Configuration::SimpleParameter<int>&); \
                                                                        \
    template bool OPERATOR(const Configuration::SimpleParameter<long>&, \
                           const Configuration::SimpleParameter<long>&); \
    template bool OPERATOR(const Configuration::SimpleParameter<long>&, const long&); \
    template bool OPERATOR(const long&, const Configuration::SimpleParameter<long>&); \
                                                                        \
    template bool OPERATOR(const Configuration::SimpleParameter<long double>&, \
                           const Configuration::SimpleParameter<long double>&); \
    template bool OPERATOR(const Configuration::SimpleParameter<long double>&, \
                           const long double&);                         \
    template bool OPERATOR(const long double&,                          \
                           const Configuration::SimpleParameter<long double>&); \
                                                                        \
    template bool OPERATOR(const Configuration::SimpleParameter<long long>&, \
                           const Configuration::SimpleParameter<long long>&); \
    template bool OPERATOR(const Configuration::SimpleParameter<long long>&, \
                           const long long&);                           \
    template bool OPERATOR(const long long&,                            \
                           const Configuration::SimpleParameter<long long>&); \
                                                                        \
    template bool OPERATOR(const Configuration::SimpleParameter<short>&, \
                           const Configuration::SimpleParameter<short>&); \
    template bool OPERATOR(const Configuration::SimpleParameter<short>&, const short&); \
    template bool OPERATOR(const short&, const Configuration::SimpleParameter<short>&); \
                                                                        \
    template bool OPERATOR(const Configuration::SimpleParameter<unsigned char>&, \
                           const Configuration::SimpleParameter<unsigned char>&); \
    template bool OPERATOR(const Configuration::SimpleParameter<unsigned char>&, \
                           const unsigned char&);                       \
    template bool OPERATOR(const unsigned char&,                        \
                           const Configuration::SimpleParameter<unsigned char>&); \
                                                                        \
    template bool OPERATOR(const Configuration::SimpleParameter<unsigned int>&, \
                           const Configuration::SimpleParameter<unsigned int>&); \
    template bool OPERATOR(const Configuration::SimpleParameter<unsigned int>&, \
                           const unsigned int&);                        \
    template bool OPERATOR(const unsigned int&,                         \
                           const Configuration::SimpleParameter<unsigned int>&); \
                                                                        \
    template bool OPERATOR(const Configuration::SimpleParameter<unsigned long>&, \
                           const Configuration::SimpleParameter<unsigned long>&); \
    template bool OPERATOR(const Configuration::SimpleParameter<unsigned long>&, \
                           const unsigned long&);                       \
    template bool OPERATOR(const unsigned long&,                        \
                           const Configuration::SimpleParameter<unsigned long>&); \
                                                                        \
    template bool OPERATOR(const Configuration::SimpleParameter<unsigned long long>&, \
                           const Configuration::SimpleParameter<unsigned long long>&); \
    template bool OPERATOR(const Configuration::SimpleParameter<unsigned long long>&, \
                           const unsigned long long&);                  \
    template bool OPERATOR(const unsigned long long&,                   \
                           const Configuration::SimpleParameter<unsigned long long>&); \
                                                                        \
    template bool OPERATOR(const Configuration::SimpleParameter<unsigned short>&, \
                           const Configuration::SimpleParameter<unsigned short>&); \
    template bool OPERATOR(const Configuration::SimpleParameter<unsigned short>&, \
                           const unsigned short&);                      \
    template bool OPERATOR(const unsigned short&,                       \
                           const Configuration::SimpleParameter<unsigned short>&);

INSTANTIATE_SIMPLE_PARAMETER_OPERATOR(operator<);
INSTANTIATE_SIMPLE_PARAMETER_OPERATOR(operator>);
INSTANTIATE_SIMPLE_PARAMETER_OPERATOR(operator<=);
INSTANTIATE_SIMPLE_PARAMETER_OPERATOR(operator>=);
INSTANTIATE_SIMPLE_PARAMETER_OPERATOR(operator==);
INSTANTIATE_SIMPLE_PARAMETER_OPERATOR(operator!=);

namespace Configuration
{
    template class SimpleParameter<std::string>;

    template class SimpleParameter<char>;
    template class SimpleParameter<double>;
    template class SimpleParameter<float>;
    template class SimpleParameter<int>;
    template class SimpleParameter<long>;
    template class SimpleParameter<long double>;
    template class SimpleParameter<long long>;
    template class SimpleParameter<short>;
    template class SimpleParameter<unsigned char>;
    template class SimpleParameter<unsigned int>;
    template class SimpleParameter<unsigned long>;
    template class SimpleParameter<unsigned long long>;
    template class SimpleParameter<unsigned short>;
}
