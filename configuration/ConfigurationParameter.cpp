#include <list>
#include <sstream>

#include "ConfigurationParameter.hpp"

//=============================================================================================
template <class T> Configuration::Parameter<T>::Parameter(const T& initial_value) :
    ParameterTemplateBase<T>(initial_value),
    RelationalParameter<T>(initial_value),
    StreamParameter<T>(initial_value)
{
    // One might think only the RelationalParameter and StreamParameter constructors need be
    // called here, because those are the two classes this class derived from, but both of
    // those classes derive from Parameter virtually. As a result, neither of them actually
    // calls the Parameter constructor, and we have to call it here ourselves.
}

//=============================================================================================
template <class T> Configuration::Parameter<std::list<T> >::Parameter(
    const std::list<T>& initial_value) :
    ParameterTemplateBase<std::list<T> >(initial_value),
    RelationalParameter<std::list<T> >(initial_value)
{
    // One might think only the RelationalParameter constructor need be called here, because
    // that is the class this class derived from, but RelationalParameter derived from
    // Parameter virtually. As a result, the RelationalParameter constructor doesn't call the
    // Parameter constructor, and we have to call it here ourselves.
}

//=============================================================================================
template <class T> Configuration::Parameter<T>::~Parameter()
{
}

//=============================================================================================
template <class T> Configuration::Parameter<std::list<T> >::~Parameter()
{
}

//=============================================================================================
template <class T>
void Configuration::Parameter<std::list<T> >::fromString(const std::string& value)
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
void Configuration::Parameter<std::list<T> >::toString(std::string& value) const
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
}
