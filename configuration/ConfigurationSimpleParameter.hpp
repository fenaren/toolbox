#if !defined CONFIGURATION_SIMPLE_PARAMETER_HPP
#define CONFIGURATION_SIMPLE_PARAMETER_HPP

#include <iostream>
#include <list>
#include <string>

#include "ConfigurationParameter.hpp"

namespace Configuration
{
    template <class T> class SimpleParameter : public Parameter<T>
    {
    public:

        explicit SimpleParameter(const T& initial_value = T());
        virtual ~SimpleParameter();

        virtual void fromString(const std::string& value);
        virtual void toString(std::string& value) const;
    };
}

template <class T>
std::istream& operator>>(std::istream& is, Configuration::SimpleParameter<T>& obj);

template <class T>
std::ostream& operator<<(std::ostream& os, const Configuration::SimpleParameter<T>& obj);

#endif
