#include <chrono>
#include <list>
#include <string>

#include "ConfigurationParameterTemplateBase.hpp"

//=============================================================================================
template <class T>
Configuration::ParameterTemplateBase<T>::ParameterTemplateBase(const T& initial_value) :
    ParameterBase(),
    value(initial_value)
{
}

//=============================================================================================
template <class T> Configuration::ParameterTemplateBase<T>::ParameterTemplateBase(
    const ParameterTemplateBase<T>& parameter) :
    ParameterBase()
{
    parameter.getValue(value);
}

//=============================================================================================
template <class T> Configuration::ParameterTemplateBase<T>::~ParameterTemplateBase()
{
}

//=============================================================================================
template <class T> Configuration::ParameterTemplateBase<T>::operator T() const
{
    return value;
}

//=============================================================================================
template <class T> void Configuration::ParameterTemplateBase<T>::setValue(const T& value)
{
    this->value = value;
    set = true;
}

//=============================================================================================
template <class T> T Configuration::ParameterTemplateBase<T>::getValue() const
{
    return value;
}

//=============================================================================================
template <class T> void Configuration::ParameterTemplateBase<T>::getValue(T& value) const
{
    value = this->value;
}

//=============================================================================================
template <class T>
Configuration::ParameterTemplateBase<T>& Configuration::ParameterTemplateBase<T>::operator=(
    const ParameterTemplateBase& parameter)
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
template <class T> Configuration::ParameterTemplateBase<T>&
Configuration::ParameterTemplateBase<T>::operator=(const T& value)
{
    this->value = value;
    set = true;

    return *this;
}

namespace Configuration
{
    // Intrinsic types
    template class ParameterTemplateBase<bool>;
    template class ParameterTemplateBase<char>;
    template class ParameterTemplateBase<double>;
    template class ParameterTemplateBase<float>;
    template class ParameterTemplateBase<int>;
    template class ParameterTemplateBase<long>;
    template class ParameterTemplateBase<long double>;
    template class ParameterTemplateBase<long long>;
    template class ParameterTemplateBase<short>;
    template class ParameterTemplateBase<unsigned char>;
    template class ParameterTemplateBase<unsigned int>;
    template class ParameterTemplateBase<unsigned long>;
    template class ParameterTemplateBase<unsigned long long>;
    template class ParameterTemplateBase<unsigned short>;

    template class ParameterTemplateBase<std::string>;
    template class ParameterTemplateBase<std::chrono::seconds>;
    template class ParameterTemplateBase<std::chrono::nanoseconds>;

    // std::lists of intrinsic types
    template class ParameterTemplateBase<std::list<bool> >;
    template class ParameterTemplateBase<std::list<char> >;
    template class ParameterTemplateBase<std::list<double> >;
    template class ParameterTemplateBase<std::list<float> >;
    template class ParameterTemplateBase<std::list<int> >;
    template class ParameterTemplateBase<std::list<long> >;
    template class ParameterTemplateBase<std::list<long double> >;
    template class ParameterTemplateBase<std::list<long long> >;
    template class ParameterTemplateBase<std::list<short> >;
    template class ParameterTemplateBase<std::list<unsigned char> >;
    template class ParameterTemplateBase<std::list<unsigned int> >;
    template class ParameterTemplateBase<std::list<unsigned long> >;
    template class ParameterTemplateBase<std::list<unsigned long long> >;
    template class ParameterTemplateBase<std::list<unsigned short> >;

    template class ParameterTemplateBase<std::list<std::string> >;
    template class ParameterTemplateBase<std::list<std::chrono::seconds> >;
    template class ParameterTemplateBase<std::list<std::chrono::nanoseconds> >;
}
