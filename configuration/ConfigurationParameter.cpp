#include <chrono>
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
    template class Parameter<std::chrono::seconds>;
    template class Parameter<std::chrono::nanoseconds>;

    // std::lists of intrinsic types
    template class Parameter<std::list<bool> >;
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
    template class Parameter<std::list<std::chrono::seconds> >;
    template class Parameter<std::list<std::chrono::nanoseconds> >;
}
