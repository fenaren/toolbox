#include <chrono>
#include <iostream>
#include <list>
#include <string>

#include "ConfigurationRelationalParameter.hpp"

//=============================================================================================
template <class T>
Configuration::RelationalParameter<T>::RelationalParameter(const T& initial_value) :
    Parameter<T>(initial_value)
{
}

//=============================================================================================
template <class T> Configuration::RelationalParameter<T>::~RelationalParameter()
{
}

//=============================================================================================
template <class T> bool operator<(const Configuration::RelationalParameter<T>& lhs,
                                  const Configuration::RelationalParameter<T>& rhs)
{
    T lhs_value;
    T rhs_value;

    lhs.getValue(lhs_value);
    rhs.getValue(rhs_value);

    return lhs_value < rhs_value;
}

//=============================================================================================
template <class T> bool operator>(const Configuration::RelationalParameter<T>& lhs,
                                  const Configuration::RelationalParameter<T>& rhs)
{
    return rhs < lhs;
}

//=============================================================================================
template <class T> bool operator<=(const Configuration::RelationalParameter<T>& lhs,
                                   const Configuration::RelationalParameter<T>& rhs)
{
    return !(lhs > rhs);
}

//=============================================================================================
template <class T> bool operator>=(const Configuration::RelationalParameter<T>& lhs,
                                   const Configuration::RelationalParameter<T>& rhs)
{
    return !(lhs < rhs);
}

//=============================================================================================
template <class T> bool operator==(const Configuration::RelationalParameter<T>& lhs,
                                   const Configuration::RelationalParameter<T>& rhs)
{
    T lhs_value;
    T rhs_value;

    lhs.getValue(lhs_value);
    rhs.getValue(rhs_value);

    return lhs_value == rhs_value;
}

//=============================================================================================
template <class T> bool operator!=(const Configuration::RelationalParameter<T>& lhs,
                                   const Configuration::RelationalParameter<T>& rhs)
{
    return !(lhs == rhs);
}

// Defining these operators is a little interesting. To make the operator comparison we have to
// change the type of one of the operators to the type of the other, but changing to the
// non-parameter type to the parameter type isn't an option, because we only know its abstract
// type here.  We have to get its value and then compare non-parameter types.

#define DEFINE_MIXED_RELATIONAL_PARAMETER_OPERATOR(OPERATOR, OP)        \
    template <class T> bool OPERATOR(const Configuration::RelationalParameter<T>& lhs, \
                                     const T&                                     rhs) \
    {                                                                   \
        T lhs_value;                                                    \
        lhs.getValue(lhs_value);                                        \
        return lhs_value OP rhs;                                        \
    }                                                                   \
                                                                        \
    template <class T> bool OPERATOR(const T&                                     lhs, \
                                     const Configuration::RelationalParameter<T>& rhs) \
    {                                                                   \
        T rhs_value;                                                    \
        rhs.getValue(rhs_value);                                        \
        return lhs OP rhs_value;                                        \
    }                                                                   \
                                                                        \
    bool OPERATOR(const Configuration::RelationalParameter<std::string>& lhs, \
                  const char*                                            rhs) \
    {                                                                   \
        std::string lhs_value;                                          \
        lhs.getValue(lhs_value);                                        \
        return lhs_value OP rhs;                                        \
    }                                                                   \
                                                                        \
    bool OPERATOR(const char*                                            lhs, \
                  const Configuration::RelationalParameter<std::string>& rhs) \
    {                                                                   \
        std::string rhs_value;                                          \
        rhs.getValue(rhs_value);                                        \
        return lhs OP rhs_value;                                        \
    }

DEFINE_MIXED_RELATIONAL_PARAMETER_OPERATOR(operator<, <);
DEFINE_MIXED_RELATIONAL_PARAMETER_OPERATOR(operator>, >);
DEFINE_MIXED_RELATIONAL_PARAMETER_OPERATOR(operator<=, <=);
DEFINE_MIXED_RELATIONAL_PARAMETER_OPERATOR(operator>=, >=);
DEFINE_MIXED_RELATIONAL_PARAMETER_OPERATOR(operator==, ==);
DEFINE_MIXED_RELATIONAL_PARAMETER_OPERATOR(operator!=, !=);

#define INSTANTIATE_RELATIONAL_PARAMETER_OPERATOR(OPERATOR)             \
    template bool OPERATOR(const Configuration::RelationalParameter<bool>&, \
                           const Configuration::RelationalParameter<bool>&); \
    template bool OPERATOR(const Configuration::RelationalParameter<bool>&, const bool&); \
    template bool OPERATOR(const bool&, const Configuration::RelationalParameter<bool>&); \
                                                                        \
    template bool OPERATOR(const Configuration::RelationalParameter<char>&, \
                           const Configuration::RelationalParameter<char>&); \
    template bool OPERATOR(const Configuration::RelationalParameter<char>&, const char&); \
    template bool OPERATOR(const char&, const Configuration::RelationalParameter<char>&); \
                                                                        \
    template bool OPERATOR(const Configuration::RelationalParameter<double>&, \
                           const Configuration::RelationalParameter<double>&); \
    template bool OPERATOR(const Configuration::RelationalParameter<double>&, const double&); \
    template bool OPERATOR(const double&, const Configuration::RelationalParameter<double>&); \
                                                                        \
    template bool OPERATOR(const Configuration::RelationalParameter<float>&, \
                           const Configuration::RelationalParameter<float>&); \
    template bool OPERATOR(const Configuration::RelationalParameter<float>&, const float&); \
    template bool OPERATOR(const float&, const Configuration::RelationalParameter<float>&); \
                                                                        \
    template bool OPERATOR(const Configuration::RelationalParameter<int>&, \
                           const Configuration::RelationalParameter<int>&); \
    template bool OPERATOR(const Configuration::RelationalParameter<int>&, const int&); \
    template bool OPERATOR(const int&, const Configuration::RelationalParameter<int>&); \
                                                                        \
    template bool OPERATOR(const Configuration::RelationalParameter<long>&, \
                           const Configuration::RelationalParameter<long>&); \
    template bool OPERATOR(const Configuration::RelationalParameter<long>&, const long&); \
    template bool OPERATOR(const long&, const Configuration::RelationalParameter<long>&); \
                                                                        \
    template bool OPERATOR(const Configuration::RelationalParameter<long double>&, \
                           const Configuration::RelationalParameter<long double>&); \
    template bool OPERATOR(const Configuration::RelationalParameter<long double>&, \
                           const long double&);                         \
    template bool OPERATOR(const long double&,                          \
                           const Configuration::RelationalParameter<long double>&); \
                                                                        \
    template bool OPERATOR(const Configuration::RelationalParameter<long long>&, \
                           const Configuration::RelationalParameter<long long>&); \
    template bool OPERATOR(const Configuration::RelationalParameter<long long>&, \
                           const long long&);                           \
    template bool OPERATOR(const long long&,                            \
                           const Configuration::RelationalParameter<long long>&); \
                                                                        \
    template bool OPERATOR(const Configuration::RelationalParameter<short>&, \
                           const Configuration::RelationalParameter<short>&); \
    template bool OPERATOR(const Configuration::RelationalParameter<short>&, const short&); \
    template bool OPERATOR(const short&, const Configuration::RelationalParameter<short>&); \
                                                                        \
    template bool OPERATOR(const Configuration::RelationalParameter<unsigned char>&, \
                           const Configuration::RelationalParameter<unsigned char>&); \
    template bool OPERATOR(const Configuration::RelationalParameter<unsigned char>&, \
                           const unsigned char&);                       \
    template bool OPERATOR(const unsigned char&,                        \
                           const Configuration::RelationalParameter<unsigned char>&); \
                                                                        \
    template bool OPERATOR(const Configuration::RelationalParameter<unsigned int>&, \
                           const Configuration::RelationalParameter<unsigned int>&); \
    template bool OPERATOR(const Configuration::RelationalParameter<unsigned int>&, \
                           const unsigned int&);                        \
    template bool OPERATOR(const unsigned int&,                         \
                           const Configuration::RelationalParameter<unsigned int>&); \
                                                                        \
    template bool OPERATOR(const Configuration::RelationalParameter<unsigned long>&, \
                           const Configuration::RelationalParameter<unsigned long>&); \
    template bool OPERATOR(const Configuration::RelationalParameter<unsigned long>&, \
                           const unsigned long&);                       \
    template bool OPERATOR(const unsigned long&,                        \
                           const Configuration::RelationalParameter<unsigned long>&); \
                                                                        \
    template bool OPERATOR(const Configuration::RelationalParameter<unsigned long long>&, \
                           const Configuration::RelationalParameter<unsigned long long>&); \
    template bool OPERATOR(const Configuration::RelationalParameter<unsigned long long>&, \
                           const unsigned long long&);                  \
    template bool OPERATOR(const unsigned long long&,                   \
                           const Configuration::RelationalParameter<unsigned long long>&); \
                                                                        \
    template bool OPERATOR(const Configuration::RelationalParameter<unsigned short>&, \
                           const Configuration::RelationalParameter<unsigned short>&); \
    template bool OPERATOR(const Configuration::RelationalParameter<unsigned short>&, \
                           const unsigned short&);                      \
    template bool OPERATOR(const unsigned short&,                       \
                           const Configuration::RelationalParameter<unsigned short>&); \
                                                                        \
    template bool OPERATOR(const Configuration::RelationalParameter<std::string>&, \
                           const Configuration::RelationalParameter<std::string>&); \
    template bool OPERATOR(const Configuration::RelationalParameter<std::string>&, \
                           const std::string&);                         \
    template bool OPERATOR(const std::string&,                          \
                           const Configuration::RelationalParameter<std::string>&);

INSTANTIATE_RELATIONAL_PARAMETER_OPERATOR(operator<);
INSTANTIATE_RELATIONAL_PARAMETER_OPERATOR(operator>);
INSTANTIATE_RELATIONAL_PARAMETER_OPERATOR(operator<=);
INSTANTIATE_RELATIONAL_PARAMETER_OPERATOR(operator>=);
INSTANTIATE_RELATIONAL_PARAMETER_OPERATOR(operator==);
INSTANTIATE_RELATIONAL_PARAMETER_OPERATOR(operator!=);

namespace Configuration
{
    // Intrinsic types
    template class RelationalParameter<bool>;
    template class RelationalParameter<char>;
    template class RelationalParameter<double>;
    template class RelationalParameter<float>;
    template class RelationalParameter<int>;
    template class RelationalParameter<long>;
    template class RelationalParameter<long double>;
    template class RelationalParameter<long long>;
    template class RelationalParameter<short>;
    template class RelationalParameter<unsigned char>;
    template class RelationalParameter<unsigned int>;
    template class RelationalParameter<unsigned long>;
    template class RelationalParameter<unsigned long long>;
    template class RelationalParameter<unsigned short>;

    template class RelationalParameter<std::string>;
    template class RelationalParameter<std::chrono::seconds>;
    template class RelationalParameter<std::chrono::nanoseconds>;

    // std::lists of intrinsic types
    template class RelationalParameter<std::list<bool> >;
    template class RelationalParameter<std::list<char> >;
    template class RelationalParameter<std::list<double> >;
    template class RelationalParameter<std::list<float> >;
    template class RelationalParameter<std::list<int> >;
    template class RelationalParameter<std::list<long> >;
    template class RelationalParameter<std::list<long double> >;
    template class RelationalParameter<std::list<long long> >;
    template class RelationalParameter<std::list<short> >;
    template class RelationalParameter<std::list<unsigned char> >;
    template class RelationalParameter<std::list<unsigned int> >;
    template class RelationalParameter<std::list<unsigned long> >;
    template class RelationalParameter<std::list<unsigned long long> >;
    template class RelationalParameter<std::list<unsigned short> >;

    template class RelationalParameter<std::list<std::string> >;
    template class RelationalParameter<std::list<std::chrono::seconds> >;
    template class RelationalParameter<std::list<std::chrono::nanoseconds> >;
}
