#if !defined CONFIGURATION_VALUE_HPP
#define CONFIGURATION_VALUE_HPP

#include <stdexcept>
#include <string>

#include "ConfigurationValueBase.hpp"

// Represents a configuration value.  They function like intrinsic types, except
// they can be "unset" or "set".  Unset configuration values have never had
// their value set after being construction, and set configuration values have.
// All the intrinsic types and std::string are supported as value types, and a
// variety of operators are overloaded to make this easy to use.
template <class T> class ConfigurationValue : public ConfigurationValueBase
{
public:

    friend class ConfigurationValue_test;

    // Constructors
    // cppcheck-suppress noExplicitConstructor
    ConfigurationValue(const T& value_default = T());
    ConfigurationValue(const ConfigurationValue& value);

    // Defines how to convert a ConfigurationValue<T> to a T
    operator T() const;

    // Destructor
    virtual ~ConfigurationValue();

    // Allows Processors to set the value regardless of templatized type.
    virtual void setValue(const std::string& value);

    // Returns the current value on the stack.  Try to use the other getValue()
    // method if T is large in memory.
    T getValue() const;

    // Returns a reference to the current value of the configuration value.
    void getValue(T& value) const;

    ConfigurationValue& operator=(const ConfigurationValue& value);
    ConfigurationValue& operator=(const T& value);

private:

    T value;
};

#define DECLARE_CONFIGURATION_VALUE_OPERATOR(OPERATOR)                  \
    template <class T> bool OPERATOR(const ConfigurationValue<T>& lhs,  \
                                     const ConfigurationValue<T>& rhs); \
    template <class T> bool OPERATOR(const ConfigurationValue<T>& lhs,  \
                                     const T&                rhs);      \
    template <class T> bool OPERATOR(const T&                lhs,       \
                                     const ConfigurationValue<T>& rhs); \
                                                                        \
    bool OPERATOR(const ConfigurationValue<std::string>& lhs,           \
                  const char* rhs);                                     \
    bool OPERATOR(const char* lhs,                                      \
                  const ConfigurationValue<std::string>& rhs);

DECLARE_CONFIGURATION_VALUE_OPERATOR(operator<);
DECLARE_CONFIGURATION_VALUE_OPERATOR(operator>);
DECLARE_CONFIGURATION_VALUE_OPERATOR(operator<=);
DECLARE_CONFIGURATION_VALUE_OPERATOR(operator>=);
DECLARE_CONFIGURATION_VALUE_OPERATOR(operator==);
DECLARE_CONFIGURATION_VALUE_OPERATOR(operator!=);

#endif
