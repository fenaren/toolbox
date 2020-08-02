#include <list>
#include <sstream>
#include <string>

#include "ConfigurationSimpleParameter.hpp"

//=============================================================================================
template <class T> Configuration::SimpleParameter<T>::SimpleParameter(const T& initial_value) :
    Parameter<T>(initial_value)
{
}

//=============================================================================================
template <class T> Configuration::SimpleParameter<T>::~SimpleParameter()
{
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

namespace Configuration
{
    // Intrinsic types
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

    template class SimpleParameter<std::string>;
}
