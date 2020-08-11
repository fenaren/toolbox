#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
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
template <class T> void Configuration::SimpleParameter<T>::toString(std::string& value) const
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
std::istream& operator>>(std::istream& is, Configuration::SimpleParameter<T>& obj)
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
std::ostream& operator<<(std::ostream& os, const Configuration::SimpleParameter<T>& obj)
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

template std::istream& operator>>(std::istream& is, Configuration::SimpleParameter<char>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::SimpleParameter<double>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::SimpleParameter<float>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::SimpleParameter<int>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::SimpleParameter<long>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::SimpleParameter<long double>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::SimpleParameter<long long>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::SimpleParameter<short>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::SimpleParameter<unsigned char>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::SimpleParameter<unsigned int>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::SimpleParameter<unsigned long>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::SimpleParameter<unsigned long long>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::SimpleParameter<unsigned short>& obj);
template std::istream& operator>>(std::istream& is,
                                  Configuration::SimpleParameter<std::string>& obj);

template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::SimpleParameter<char>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::SimpleParameter<double>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::SimpleParameter<float>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::SimpleParameter<int>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::SimpleParameter<long>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::SimpleParameter<long double>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::SimpleParameter<long long>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::SimpleParameter<short>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::SimpleParameter<unsigned char>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::SimpleParameter<unsigned int>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::SimpleParameter<unsigned long>& obj);
template std::ostream& operator<<(
    std::ostream& os, const Configuration::SimpleParameter<unsigned long long>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::SimpleParameter<unsigned short>& obj);
template std::ostream& operator<<(std::ostream& os,
                                  const Configuration::SimpleParameter<std::string>& obj);
