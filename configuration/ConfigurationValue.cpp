#include <sstream>
#include <stdexcept>
#include <string>

#include "ConfigurationValue.hpp"

#define DEFINE_MIXED_CONFIGURATION_VALUE_OPERATOR(OPERATOR, OP) \
    template <class T>                                          \
    bool OPERATOR(const ConfigurationValue<T>& lhs,             \
                  const T&                     rhs)             \
    {                                                           \
        return lhs OP ConfigurationValue<T>(rhs);               \
    }                                                           \
                                                                \
    template <class T>                                          \
    bool OPERATOR(const T&                     lhs,             \
                  const ConfigurationValue<T>& rhs)             \
    {                                                           \
        return ConfigurationValue<T>(lhs) OP rhs;               \
    }                                                           \
                                                                \
    bool OPERATOR(const ConfigurationValue<std::string>& lhs,   \
                  const char*                            rhs)   \
    {                                                           \
        return lhs OP ConfigurationValue<std::string>(rhs);     \
    }                                                           \
                                                                \
    bool OPERATOR(const char* lhs,                              \
                  const ConfigurationValue<std::string>& rhs)   \
    {                                                           \
        return ConfigurationValue<std::string>(lhs) OP rhs;     \
    }

//==============================================================================
template <class T>
ConfigurationValue<T>::ConfigurationValue(const T& default_value) :
    value(default_value),
    set(false)
{
}

//==============================================================================
template <class T> ConfigurationValue<T>::~ConfigurationValue()
{
}

//==============================================================================
template <class T>
void ConfigurationValue<T>::setValue(const std::string& value)
{
    std::istringstream converter(value);
    converter >> this->value;

    // Did the conversion go okay?
    if (!converter)
    {
        throw std::runtime_error("Error converting value to template type");
    }

    set = true;
}

//==============================================================================
template <class T> T ConfigurationValue<T>::getValue() const
{
    return value;
}

//==============================================================================
template <class T> void ConfigurationValue<T>::getValue(T& value) const
{
    value = this->value;
}

//==============================================================================
template <class T> ConfigurationValue<T>&
ConfigurationValue<T>::operator=(const ConfigurationValue& configuration_value)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &configuration_value)
    {
        value = configuration_value.value;
        set   = configuration_value.set;
    }

    return *this;
}

//==============================================================================
template <class T>
ConfigurationValue<T>& ConfigurationValue<T>::operator=(const T& value)
{
    this->value = value;
    set = true;

    return *this;
}

//==============================================================================
template <class T> bool
operator<(const ConfigurationValue<T>& lhs, const ConfigurationValue<T>& rhs)
{
    T lhs_value;
    T rhs_value;

    lhs.getValue(lhs_value);
    rhs.getValue(rhs_value);

    return lhs_value < rhs_value;
}

DEFINE_MIXED_CONFIGURATION_VALUE_OPERATOR(operator<, <);

//==============================================================================
template <class T> bool
operator>(const ConfigurationValue<T>& lhs, const ConfigurationValue<T>& rhs)
{
    return rhs < lhs;
}

DEFINE_MIXED_CONFIGURATION_VALUE_OPERATOR(operator>, >);

//==============================================================================
template <class T> bool
operator<=(const ConfigurationValue<T>& lhs, const ConfigurationValue<T>& rhs)
{
    return !(lhs > rhs);
}

DEFINE_MIXED_CONFIGURATION_VALUE_OPERATOR(operator<=, <=);

//==============================================================================
template <class T> bool
operator>=(const ConfigurationValue<T>& lhs, const ConfigurationValue<T>& rhs)
{
    return !(lhs < rhs);
}

DEFINE_MIXED_CONFIGURATION_VALUE_OPERATOR(operator>=, >=);

//==============================================================================
template <class T> bool
operator==(const ConfigurationValue<T>& lhs, const ConfigurationValue<T>& rhs)
{
    T lhs_value;
    T rhs_value;

    lhs.getValue(lhs_value);
    rhs.getValue(rhs_value);

    return lhs_value == rhs_value;
}

DEFINE_MIXED_CONFIGURATION_VALUE_OPERATOR(operator==, ==);

//==============================================================================
template <class T> bool
operator!=(const ConfigurationValue<T>& lhs, const ConfigurationValue<T>& rhs)
{
    return !(lhs == rhs);
}

DEFINE_MIXED_CONFIGURATION_VALUE_OPERATOR(operator!=, !=);

template class ConfigurationValue<std::string>;

template class ConfigurationValue<char>;
template class ConfigurationValue<double>;
template class ConfigurationValue<float>;
template class ConfigurationValue<int>;
template class ConfigurationValue<long>;
template class ConfigurationValue<long double>;
template class ConfigurationValue<long long>;
template class ConfigurationValue<short>;
template class ConfigurationValue<unsigned char>;
template class ConfigurationValue<unsigned int>;
template class ConfigurationValue<unsigned long>;
template class ConfigurationValue<unsigned long long>;
template class ConfigurationValue<unsigned short>;

#define INSTANTIATE_CONFIGURATION_VALUE_OPERATOR(OPERATOR)              \
    template bool                                                       \
    OPERATOR(const ConfigurationValue<std::string>&,                    \
             const ConfigurationValue<std::string>&);                   \
                                                                        \
    template bool                                                       \
    OPERATOR(const ConfigurationValue<std::string>&,                    \
             const std::string&);                                       \
    template bool                                                       \
    OPERATOR(const std::string&,                                        \
             const ConfigurationValue<std::string>&);                   \
                                                                        \
    template bool OPERATOR(const ConfigurationValue<char>&,             \
                           const ConfigurationValue<char>&);            \
    template bool OPERATOR(const ConfigurationValue<char>&, const char&); \
    template bool OPERATOR(const char&, const ConfigurationValue<char>&); \
                                                                        \
    template bool OPERATOR(const ConfigurationValue<double>&,           \
                           const ConfigurationValue<double>&);          \
    template bool OPERATOR(const ConfigurationValue<double>&, const double&); \
    template bool OPERATOR(const double&, const ConfigurationValue<double>&); \
                                                                        \
    template bool OPERATOR(const ConfigurationValue<float>&,            \
                           const ConfigurationValue<float>&);           \
    template bool OPERATOR(const ConfigurationValue<float>&, const float&); \
    template bool OPERATOR(const float&, const ConfigurationValue<float>&); \
                                                                        \
    template bool OPERATOR(const ConfigurationValue<int>&,              \
                           const ConfigurationValue<int>&);             \
    template bool OPERATOR(const ConfigurationValue<int>&, const int&); \
    template bool OPERATOR(const int&, const ConfigurationValue<int>&); \
                                                                        \
    template bool OPERATOR(const ConfigurationValue<long>&,             \
                           const ConfigurationValue<long>&);            \
    template bool OPERATOR(const ConfigurationValue<long>&, const long&); \
    template bool OPERATOR(const long&, const ConfigurationValue<long>&); \
                                                                        \
    template bool OPERATOR(const ConfigurationValue<long double>&,      \
                           const ConfigurationValue<long double>&);     \
    template bool OPERATOR(const ConfigurationValue<long double>&,      \
                           const long double&);                         \
    template bool OPERATOR(const long double&,                          \
                           const ConfigurationValue<long double>&);     \
                                                                        \
    template bool OPERATOR(const ConfigurationValue<long long>&,        \
                           const ConfigurationValue<long long>&);       \
    template bool OPERATOR(const ConfigurationValue<long long>&,        \
                           const long long&);                           \
    template bool OPERATOR(const long long&,                            \
                           const ConfigurationValue<long long>&);       \
                                                                        \
    template bool OPERATOR(const ConfigurationValue<short>&,            \
                           const ConfigurationValue<short>&);           \
    template bool OPERATOR(const ConfigurationValue<short>&,            \
                           const short&);                               \
    template bool OPERATOR(const short&,                                \
                           const ConfigurationValue<short>&);           \
                                                                        \
    template bool OPERATOR(const ConfigurationValue<unsigned char>&,    \
                           const ConfigurationValue<unsigned char>&);   \
    template bool OPERATOR(const ConfigurationValue<unsigned char>&,    \
                           const unsigned char&);                       \
    template bool OPERATOR(const unsigned char&,                        \
                           const ConfigurationValue<unsigned char>&);   \
                                                                        \
    template bool OPERATOR(const ConfigurationValue<unsigned int>&,     \
                           const ConfigurationValue<unsigned int>&);    \
    template bool OPERATOR(const ConfigurationValue<unsigned int>&,     \
                           const unsigned int&);                        \
    template bool OPERATOR(const unsigned int&,                         \
                           const ConfigurationValue<unsigned int>&);    \
                                                                        \
    template bool OPERATOR(const ConfigurationValue<unsigned long>&,    \
                           const ConfigurationValue<unsigned long>&);   \
    template bool OPERATOR(const ConfigurationValue<unsigned long>&,    \
                           const unsigned long&);                       \
    template bool OPERATOR(const unsigned long&,                        \
                           const ConfigurationValue<unsigned long>&);   \
                                                                        \
    template bool OPERATOR(const ConfigurationValue<unsigned long long>&, \
                           const ConfigurationValue<unsigned long long>&); \
    template bool OPERATOR(const ConfigurationValue<unsigned long long>&, \
                           const unsigned long long&);                  \
    template bool OPERATOR(const unsigned long long&,                   \
                           const ConfigurationValue<unsigned long long>&); \
                                                                        \
    template bool OPERATOR(const ConfigurationValue<unsigned short>&,   \
                           const ConfigurationValue<unsigned short>&);  \
    template bool OPERATOR(const ConfigurationValue<unsigned short>&,   \
                           const unsigned short&);                      \
    template bool OPERATOR(const unsigned short&,                       \
                           const ConfigurationValue<unsigned short>&);

INSTANTIATE_CONFIGURATION_VALUE_OPERATOR(operator<);
INSTANTIATE_CONFIGURATION_VALUE_OPERATOR(operator>);
INSTANTIATE_CONFIGURATION_VALUE_OPERATOR(operator<=);
INSTANTIATE_CONFIGURATION_VALUE_OPERATOR(operator>=);
INSTANTIATE_CONFIGURATION_VALUE_OPERATOR(operator==);
INSTANTIATE_CONFIGURATION_VALUE_OPERATOR(operator!=);
