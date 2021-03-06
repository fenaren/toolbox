#include <string>

#include "ConfigurationNoopParameter.hpp"

#include "ConfigurationRelationalParameter.hpp"
#include "ConfigurationParameterTemplateBase.hpp"

//=============================================================================================
template <class T> Configuration::NoopParameter<T>::NoopParameter(const T& initial_value) :
    ParameterTemplateBase<T>(initial_value),
    RelationalParameter<T>(initial_value)
{
    // One might think only the RelationalParameter constructor need be called here, because
    // that is the class this class derived from, but RelationalParameter derived from
    // Parameter virtually. As a result, the RelationalParameter constructor doesn't call the
    // Parameter constructor, and we have to call it here ourselves.
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
    template class NoopParameter<bool>;
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
