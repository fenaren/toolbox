#if !defined CONFIGURATION_PARAMETER_HPP
#define CONFIGURATION_PARAMETER_HPP

#include <stdexcept>
#include <string>

#include "ConfigurationParameterBase.hpp"

namespace Configuration
{
    // ConfigurationParameter is a class for associating a small amount of metadata (the "set"
    // field) with a piece of data (the "value" field).  It's a simple implementation of the
    // data element concept (see "https://en.wikipedia.org/wiki/Data_element").
    template <class T> class Parameter : public ParameterBase
    {
    public:

        friend class Parameter_test;

        // cppcheck-suppress noExplicitConstructor
        Parameter(const T& initial_value = T());
        Parameter(const Parameter& parameter);

        virtual ~Parameter();

        // Defines how to convert a Parameter<T> to a T
        operator T() const;

        void setValue(const T& value);

        // Returns the current value on the stack.  Try to use the other getValue() method if T
        // is large in memory.
        T getValue() const;

        // Returns a reference to the current value of the configuration parameter.
        void getValue(T& value) const;

        Parameter& operator=(const Parameter& parameter);
        Parameter& operator=(const T& parameter);

    protected:

        T value;
    };
}

#define DECLARE_CONFIGURATION_PARAMETER_OPERATOR(OPERATOR)              \
    template <class T> bool OPERATOR(const Configuration::Parameter<T>& lhs, \
                                     const Configuration::Parameter<T>& rhs); \
    template <class T> bool OPERATOR(const Configuration::Parameter<T>& lhs, \
                                     const T&                           rhs); \
    template <class T> bool OPERATOR(const T&                           lhs, \
                                     const Configuration::Parameter<T>& rhs); \
                                                                        \
    bool OPERATOR(const Configuration::Parameter<std::string>& lhs,     \
                  const char*                                  rhs);    \
    bool OPERATOR(const char*                                  lhs,     \
                  const Configuration::Parameter<std::string>& rhs);

DECLARE_CONFIGURATION_PARAMETER_OPERATOR(operator<);
DECLARE_CONFIGURATION_PARAMETER_OPERATOR(operator>);
DECLARE_CONFIGURATION_PARAMETER_OPERATOR(operator<=);
DECLARE_CONFIGURATION_PARAMETER_OPERATOR(operator>=);
DECLARE_CONFIGURATION_PARAMETER_OPERATOR(operator==);
DECLARE_CONFIGURATION_PARAMETER_OPERATOR(operator!=);

#endif
