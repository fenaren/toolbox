#include <list>
#include <sstream>

#include "ConfigurationSimpleParameter.hpp"

//=============================================================================================
template <class T> Configuration::SimpleParameter<T>::SimpleParameter(const T& initial_value) :
    Parameter<T>(initial_value),
    RelationalParameter<T>(initial_value),
    StreamParameter<T>(initial_value)
{
}

//=============================================================================================
template <class T> Configuration::SimpleParameter<std::list<T> >::SimpleParameter(
    const std::list<T>& initial_value) :
    Parameter<std::list<T> >(initial_value),
    RelationalParameter<std::list<T> >(initial_value)
{
}

//=============================================================================================
template <class T> Configuration::SimpleParameter<T>::~SimpleParameter()
{
}

//=============================================================================================
template <class T> Configuration::SimpleParameter<std::list<T> >::~SimpleParameter()
{
}

//=============================================================================================
template <class T>
void Configuration::SimpleParameter<std::list<T> >::fromString(const std::string& value)
{
    std::istringstream instream(value);
    if (!instream)
    {
        throw std::runtime_error("String could not be processed");
    }

    T element;
    while(instream >> element)
    {
        this->value.push_back(element);
    }

    // We're done, but why are we done?  If something went wrong report it.
    if (instream.bad())
    {
        throw std::runtime_error("I/O error while processing");
    }
}

//=============================================================================================
template <class T>
void Configuration::SimpleParameter<std::list<T> >::toString(std::string& value) const
{
    std::ostringstream outstream;
    for (typename std::list<T>::const_iterator i = this->value.begin();
         i != this->value.end();
         ++i)
    {
        if (i != this->value.begin())
        {
            outstream << " ";
        }

        outstream << *i;
    }

    value = outstream.str();
}

namespace Configuration
{
    // Intrinsic types
    template class SimpleParameter<bool>;
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

    // std::lists of intrinsic types
    template class SimpleParameter<std::list<bool> >;
    template class SimpleParameter<std::list<char> >;
    template class SimpleParameter<std::list<double> >;
    template class SimpleParameter<std::list<float> >;
    template class SimpleParameter<std::list<int> >;
    template class SimpleParameter<std::list<long> >;
    template class SimpleParameter<std::list<long double> >;
    template class SimpleParameter<std::list<long long> >;
    template class SimpleParameter<std::list<short> >;
    template class SimpleParameter<std::list<unsigned char> >;
    template class SimpleParameter<std::list<unsigned int> >;
    template class SimpleParameter<std::list<unsigned long> >;
    template class SimpleParameter<std::list<unsigned long long> >;
    template class SimpleParameter<std::list<unsigned short> >;

    template class SimpleParameter<std::list<std::string> >;
}
