#if !defined CONFIGURATION_SIMPLE_PARAMETER_HPP
#define CONFIGURATION_SIMPLE_PARAMETER_HPP

#include <stdexcept>
#include <string>

#include "ConfigurationParameter.hpp"

namespace Configuration
{
    // SimpleConfigurationParameter is a class for associating a small amount of metadata (the
    // "set" field) with a piece of data (the "value" field).  It's a simple implementation of
    // the data element concept (see "https://en.wikipedia.org/wiki/Data_element").
    template <class T> class SimpleParameter : public Parameter
    {
    public:

        friend class SimpleParameter_test;

        // cppcheck-suppress noExplicitConstructor
        SimpleParameter(const T& initial_value = T());
        SimpleParameter(const SimpleParameter& parameter);

        virtual ~SimpleParameter();

        // Defines how to convert a SimpleParameter<T> to a T
        operator T() const;

        void setValue(const T& value);

        // Returns the current value on the stack.  Try to use the other getValue() method if T
        // is large in memory.
        T getValue() const;

        // Returns a reference to the current value of the configuration parameter.
        void getValue(T& value) const;

        virtual void fromString(const std::string& value);
        virtual void toString(std::string& value) const;

        SimpleParameter& operator=(const SimpleParameter& parameter);
        SimpleParameter& operator=(const T& parameter);

    private:

        T value;
    };
}

#define DECLARE_CONFIGURATION_SIMPLE_PARAMETER_OPERATOR(OPERATOR)       \
    template <class T> bool OPERATOR(const Configuration::SimpleParameter<T>& lhs, \
                                     const Configuration::SimpleParameter<T>& rhs); \
    template <class T> bool OPERATOR(const Configuration::SimpleParameter<T>& lhs, \
                                     const T&                  rhs);    \
    template <class T> bool OPERATOR(const T&                  lhs,     \
                                     const Configuration::SimpleParameter<T>& rhs); \
                                                                        \
    bool OPERATOR(const Configuration::SimpleParameter<std::string>& lhs, \
                  const char*                         rhs);             \
    bool OPERATOR(const char*                         lhs,              \
                  const Configuration::SimpleParameter<std::string>& rhs);

DECLARE_CONFIGURATION_SIMPLE_PARAMETER_OPERATOR(operator<);
DECLARE_CONFIGURATION_SIMPLE_PARAMETER_OPERATOR(operator>);
DECLARE_CONFIGURATION_SIMPLE_PARAMETER_OPERATOR(operator<=);
DECLARE_CONFIGURATION_SIMPLE_PARAMETER_OPERATOR(operator>=);
DECLARE_CONFIGURATION_SIMPLE_PARAMETER_OPERATOR(operator==);
DECLARE_CONFIGURATION_SIMPLE_PARAMETER_OPERATOR(operator!=);


#endif
