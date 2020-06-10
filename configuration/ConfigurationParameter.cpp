#include <sstream>
#include <stdexcept>
#include <string>

#include "ConfigurationParameter.hpp"

#define DEFINE_MIXED_PARAMETER_OPERATOR(OPERATOR, OP)                   \
    template <class T> bool OPERATOR(const Parameter<T>& lhs, const T& rhs) \
    {                                                                   \
        return lhs OP Parameter<T>(rhs);                                \
    }                                                                   \
                                                                        \
    template <class T> bool OPERATOR(const T& lhs, const Parameter<T>& rhs) \
    {                                                                   \
        return Parameter<T>(lhs) OP rhs;                                \
    }                                                                   \
                                                                        \
    bool OPERATOR(const Parameter<std::string>& lhs, const char* rhs)   \
    {                                                                   \
        return lhs OP Parameter<std::string>(rhs);                      \
    }                                                                   \
                                                                        \
    bool OPERATOR(const char* lhs, const Parameter<std::string>& rhs)   \
    {                                                                   \
        return Parameter<std::string>(lhs) OP rhs;                      \
    }

namespace Configuration
{
    //=========================================================================================
    template <class T> Parameter<T>::Parameter(const T& initial_value) :
        ParameterBase(),
        value(initial_value)
    {
    }

    //=========================================================================================
    template <class T> Parameter<T>::Parameter(const Parameter<T>& parameter) :
        ParameterBase()
    {
        parameter.getValue(value);
    }

    //=========================================================================================
    template <class T> Parameter<T>::operator T() const
    {
        return value;
    }

    //=========================================================================================
    template <class T> Parameter<T>::~Parameter()
    {
    }

    //=========================================================================================
    template <class T> void Parameter<T>::setValue(const std::string& value)
    {
        std::istringstream converter(value);

        T value_temp;
        converter >> value_temp;

        // Did the conversion go okay?
        if (!converter)
        {
            throw std::runtime_error("Error converting value to template type");
        }

        this->value = value_temp;
        set();
    }

    //=========================================================================================
    template <class T> T Parameter<T>::getValue() const
    {
        return value;
    }

    //=========================================================================================
    template <class T> void Parameter<T>::getValue(T& value) const
    {
        value = this->value;
    }

    //=========================================================================================
    template <class T> Parameter<T>& Parameter<T>::operator=(const Parameter& parameter)
    {
        // Don't do anything if we're assigning to ourselves
        if (this != &parameter)
        {
            value = parameter.value;
            set();
        }

        return *this;
    }

    //=========================================================================================
    template <class T> Parameter<T>& Parameter<T>::operator=(const T& value)
    {
        this->value = value;
        set();

        return *this;
    }

    //=========================================================================================
    template <class T> bool operator<(const Parameter<T>& lhs, const Parameter<T>& rhs)
    {
        T lhs_value;
        T rhs_value;

        lhs.getValue(lhs_value);
        rhs.getValue(rhs_value);

        return lhs_value < rhs_value;
    }

    DEFINE_MIXED_PARAMETER_OPERATOR(operator<, <);

    //=========================================================================================
    template <class T> bool operator>(const Parameter<T>& lhs, const Parameter<T>& rhs)
    {
        return rhs < lhs;
    }

    DEFINE_MIXED_PARAMETER_OPERATOR(operator>, >);

    //=========================================================================================
    template <class T> bool operator<=(const Parameter<T>& lhs, const Parameter<T>& rhs)
    {
        return !(lhs > rhs);
    }

    DEFINE_MIXED_PARAMETER_OPERATOR(operator<=, <=);

    //=========================================================================================
    template <class T> bool operator>=(const Parameter<T>& lhs, const Parameter<T>& rhs)
    {
        return !(lhs < rhs);
    }

    DEFINE_MIXED_PARAMETER_OPERATOR(operator>=, >=);

    //=========================================================================================
    template <class T> bool operator==(const Parameter<T>& lhs, const Parameter<T>& rhs)
    {
        T lhs_value;
        T rhs_value;

        lhs.getValue(lhs_value);
        rhs.getValue(rhs_value);

        return lhs_value == rhs_value;
    }

    DEFINE_MIXED_PARAMETER_OPERATOR(operator==, ==);

    //=========================================================================================
    template <class T> bool operator!=(const Parameter<T>& lhs, const Parameter<T>& rhs)
    {
        return !(lhs == rhs);
    }

    DEFINE_MIXED_PARAMETER_OPERATOR(operator!=, !=);

    template class Parameter<std::string>;

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

#define INSTANTIATE_PARAMETER_OPERATOR(OPERATOR)                        \
    template bool                                                       \
    OPERATOR(const Parameter<std::string>&,                             \
             const Parameter<std::string>&);                            \
                                                                        \
    template bool                                                       \
    OPERATOR(const Parameter<std::string>&,                             \
             const std::string&);                                       \
    template bool                                                       \
    OPERATOR(const std::string&,                                        \
             const Parameter<std::string>&);                            \
                                                                        \
    template bool OPERATOR(const Parameter<char>&,                      \
                           const Parameter<char>&);                     \
    template bool OPERATOR(const Parameter<char>&, const char&);        \
    template bool OPERATOR(const char&, const Parameter<char>&);        \
                                                                        \
    template bool OPERATOR(const Parameter<double>&,                    \
                           const Parameter<double>&);                   \
    template bool OPERATOR(const Parameter<double>&, const double&);    \
    template bool OPERATOR(const double&, const Parameter<double>&);    \
                                                                        \
    template bool OPERATOR(const Parameter<float>&,                     \
                           const Parameter<float>&);                    \
    template bool OPERATOR(const Parameter<float>&, const float&);      \
    template bool OPERATOR(const float&, const Parameter<float>&);      \
                                                                        \
    template bool OPERATOR(const Parameter<int>&,                       \
                           const Parameter<int>&);                      \
    template bool OPERATOR(const Parameter<int>&, const int&);          \
    template bool OPERATOR(const int&, const Parameter<int>&);          \
                                                                        \
    template bool OPERATOR(const Parameter<long>&,                      \
                           const Parameter<long>&);                     \
    template bool OPERATOR(const Parameter<long>&, const long&);        \
    template bool OPERATOR(const long&, const Parameter<long>&);        \
                                                                        \
    template bool OPERATOR(const Parameter<long double>&,               \
                           const Parameter<long double>&);              \
    template bool OPERATOR(const Parameter<long double>&,               \
                           const long double&);                         \
    template bool OPERATOR(const long double&,                          \
                           const Parameter<long double>&);              \
                                                                        \
    template bool OPERATOR(const Parameter<long long>&,                 \
                           const Parameter<long long>&);                \
    template bool OPERATOR(const Parameter<long long>&,                 \
                           const long long&);                           \
    template bool OPERATOR(const long long&,                            \
                           const Parameter<long long>&);                \
                                                                        \
    template bool OPERATOR(const Parameter<short>&,                     \
                           const Parameter<short>&);                    \
    template bool OPERATOR(const Parameter<short>&,                     \
                           const short&);                               \
    template bool OPERATOR(const short&,                                \
                           const Parameter<short>&);                    \
                                                                        \
    template bool OPERATOR(const Parameter<unsigned char>&,             \
                           const Parameter<unsigned char>&);            \
    template bool OPERATOR(const Parameter<unsigned char>&,             \
                           const unsigned char&);                       \
    template bool OPERATOR(const unsigned char&,                        \
                           const Parameter<unsigned char>&);            \
                                                                        \
    template bool OPERATOR(const Parameter<unsigned int>&,              \
                           const Parameter<unsigned int>&);             \
    template bool OPERATOR(const Parameter<unsigned int>&,              \
                           const unsigned int&);                        \
    template bool OPERATOR(const unsigned int&,                         \
                           const Parameter<unsigned int>&);             \
                                                                        \
    template bool OPERATOR(const Parameter<unsigned long>&,             \
                           const Parameter<unsigned long>&);            \
    template bool OPERATOR(const Parameter<unsigned long>&,             \
                           const unsigned long&);                       \
    template bool OPERATOR(const unsigned long&,                        \
                           const Parameter<unsigned long>&);            \
                                                                        \
    template bool OPERATOR(const Parameter<unsigned long long>&,        \
                           const Parameter<unsigned long long>&);       \
    template bool OPERATOR(const Parameter<unsigned long long>&,        \
                           const unsigned long long&);                  \
    template bool OPERATOR(const unsigned long long&,                   \
                           const Parameter<unsigned long long>&);       \
                                                                        \
    template bool OPERATOR(const Parameter<unsigned short>&,            \
                           const Parameter<unsigned short>&);           \
    template bool OPERATOR(const Parameter<unsigned short>&,            \
                           const unsigned short&);                      \
    template bool OPERATOR(const unsigned short&,                       \
                           const Parameter<unsigned short>&);

    INSTANTIATE_PARAMETER_OPERATOR(operator<);
    INSTANTIATE_PARAMETER_OPERATOR(operator>);
    INSTANTIATE_PARAMETER_OPERATOR(operator<=);
    INSTANTIATE_PARAMETER_OPERATOR(operator>=);
    INSTANTIATE_PARAMETER_OPERATOR(operator==);
    INSTANTIATE_PARAMETER_OPERATOR(operator!=);
}
