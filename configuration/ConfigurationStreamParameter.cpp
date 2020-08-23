#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <string>

#include "ConfigurationStreamParameter.hpp"

//=============================================================================================
template <class T> Configuration::StreamParameter<T>::StreamParameter(const T& initial_value) :
    ParameterTemplateBase<T>(initial_value)
{
}

//=============================================================================================
template <class T> Configuration::StreamParameter<T>::~StreamParameter()
{
}

//=============================================================================================
template <class T> void Configuration::StreamParameter<T>::fromString(const std::string& value)
{
    std::istringstream is(value);
    if (!is)
    {
        throw std::runtime_error("String could not be processed");
    }

    is >> this->value;

    // If something went wrong report it
    if (is.bad())
    {
        throw std::runtime_error("I/O error while processing");
    }
    else if (!is.eof() && is.fail())
    {
        throw std::runtime_error("Error converting to parameter type");
    }
}

//=============================================================================================
template <class T> void Configuration::StreamParameter<T>::toString(std::string& value) const
{
    std::ostringstream os;
    os << this->value;

    // If something went wrong report it
    if (os.bad())
    {
        throw std::runtime_error("I/O error while processing");
    }
    else if (!os.eof() && os.fail())
    {
        throw std::runtime_error("Error converting to parameter type");
    }

    value = os.str();
}

//=============================================================================================
template <class T>
std::istream& operator>>(std::istream& is, Configuration::StreamParameter<T>& obj)
{
    T obj_value;
    is >> obj_value;

    // If something went wrong report it
    if (is.bad())
    {
        throw std::runtime_error("I/O error while processing");
    }
    else if (!is.eof() && is.fail())
    {
        throw std::runtime_error("Error converting to parameter type");
    }

    obj.setValue(obj_value);

    return is;
}

//=============================================================================================
template <class T>
std::ostream& operator<<(std::ostream& os, const Configuration::StreamParameter<T>& obj)
{
    os << obj.getValue();

    // If something went wrong report it
    if (os.bad())
    {
        throw std::runtime_error("I/O error while processing");
    }
    else if (!os.eof() && os.fail())
    {
        throw std::runtime_error("Error converting to parameter type");
    }

    return os;
}

namespace Configuration
{
    // Intrinsic types
    template class StreamParameter<bool>;
    template class StreamParameter<char>;
    template class StreamParameter<double>;
    template class StreamParameter<float>;
    template class StreamParameter<int>;
    template class StreamParameter<long>;
    template class StreamParameter<long double>;
    template class StreamParameter<long long>;
    template class StreamParameter<short>;
    template class StreamParameter<unsigned char>;
    template class StreamParameter<unsigned int>;
    template class StreamParameter<unsigned long>;
    template class StreamParameter<unsigned long long>;
    template class StreamParameter<unsigned short>;

    template class StreamParameter<std::string>;
}

template std::istream& operator>>(std::istream& is, Configuration::StreamParameter<bool>& obj);
template std::istream& operator>>(std::istream& is, Configuration::StreamParameter<char>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::StreamParameter<double>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::StreamParameter<float>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::StreamParameter<int>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::StreamParameter<long>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::StreamParameter<long double>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::StreamParameter<long long>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::StreamParameter<short>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::StreamParameter<unsigned char>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::StreamParameter<unsigned int>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::StreamParameter<unsigned long>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::StreamParameter<unsigned long long>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::StreamParameter<unsigned short>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::StreamParameter<std::string>& obj);

template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::StreamParameter<bool>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::StreamParameter<char>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::StreamParameter<double>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::StreamParameter<float>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::StreamParameter<int>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::StreamParameter<long>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::StreamParameter<long double>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::StreamParameter<long long>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::StreamParameter<short>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::StreamParameter<unsigned char>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::StreamParameter<unsigned int>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::StreamParameter<unsigned long>& obj);
template std::ostream& operator<<(
    std::ostream& os, const Configuration::StreamParameter<unsigned long long>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::StreamParameter<unsigned short>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::StreamParameter<std::string>& obj);
