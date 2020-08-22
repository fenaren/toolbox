#if !defined CONFIGURATION_STREAM_PARAMETER_HPP
#define CONFIGURATION_STREAM_PARAMETER_HPP

#include <iostream>
#include <string>

#include "ConfigurationParameter.hpp"

namespace Configuration
{
    // Takes the definitions provided by the Parameter base class and adds stream insertion and
    // extraction definitions.
    template <class T> class StreamParameter : virtual public Parameter<T>
    {
    public:

        friend class StreamParameter_test;

        explicit StreamParameter(const T& initial_value = T());
        virtual ~StreamParameter();

        virtual void fromString(const std::string& value);
        virtual void toString(std::string& value) const;
    };
}

template <class T>
std::istream& operator>>(std::istream& is, Configuration::StreamParameter<T>& obj);

template <class T>
std::ostream& operator<<(std::ostream& os, const Configuration::StreamParameter<T>& obj);

#endif
