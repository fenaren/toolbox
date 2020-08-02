#include <string>

#include "ConfigurationNoopParameter.hpp"

//=============================================================================================
template <class T> Configuration::NoopParameter<T>::NoopParameter(const T& initial_value) :
    Parameter<T>(initial_value)
{
}

//=============================================================================================
template <class T> Configuration::NoopParameter<T>::~NoopParameter()
{
}

//=============================================================================================
template <class T> void Configuration::NoopParameter<T>::fromString(const std::string& value)
{
    // Intentionally left blank
}

//=============================================================================================
template <class T> void Configuration::NoopParameter<T>::toString(std::string& value) const
{
    // Intentionally left blank
}

namespace Configuration
{
    // Intrinsic types
    template class NoopParameter<char>;
    template class NoopParameter<double>;
    template class NoopParameter<float>;
    template class NoopParameter<int>;
    template class NoopParameter<long>;
    template class NoopParameter<long double>;
    template class NoopParameter<long long>;
    template class NoopParameter<short>;
    template class NoopParameter<unsigned char>;
    template class NoopParameter<unsigned int>;
    template class NoopParameter<unsigned long>;
    template class NoopParameter<unsigned long long>;
    template class NoopParameter<unsigned short>;

    template class NoopParameter<std::string>;
}
