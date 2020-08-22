#include <list>
#include <sstream>
#include <stdexcept>
#include <string>

#include "ConfigurationListParameter.hpp"

//=============================================================================================
template <class T>
Configuration::ListParameter<T>::ListParameter(const std::list<T>& initial_value) :
    RelationalParameter<std::list<T> >(initial_value)
{
}

//=============================================================================================
template <class T> Configuration::ListParameter<T>::~ListParameter()
{
}

//=============================================================================================
template <class T> void Configuration::ListParameter<T>::fromString(const std::string& value)
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
template <class T> void Configuration::ListParameter<T>::toString(std::string& value) const
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
    template class ListParameter<char>;
    template class ListParameter<double>;
    template class ListParameter<float>;
    template class ListParameter<int>;
    template class ListParameter<long>;
    template class ListParameter<long double>;
    template class ListParameter<long long>;
    template class ListParameter<short>;
    template class ListParameter<unsigned char>;
    template class ListParameter<unsigned int>;
    template class ListParameter<unsigned long>;
    template class ListParameter<unsigned long long>;
    template class ListParameter<unsigned short>;

    template class ListParameter<std::string>;
}
