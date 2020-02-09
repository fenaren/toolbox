#if !defined CONFIGURATION_VALUE_HPP
#define CONFIGURATION_VALUE_HPP

#include <stdexcept>
#include <string>

#include "ConfigurationValueBase.hpp"

// Represents an argument with a single value.  All the intrinsic types and
// std::string are supported as value types, and a variety of operators are
// overloaded to make this easy to use.
template <class T> class ConfigurationValue : public ConfigurationValueBase
{
public:

    friend class ConfigurationValue_test;

    // Constructors
    // cppcheck-suppress noExplicitConstructor
    ConfigurationValue(const T& value_default = T());
    ConfigurationValue(const ConfigurationValue& value);

    // Destructor
    virtual ~ConfigurationValue();

    // Returns true if this argument has ever been set with any of the
    // setValue() methods.
    bool isSet() const;

    // Allows Processors to set the value regardless of templatized type
    virtual void setValue(const std::string& value);

    // Use this if the type is known
    void setValue(const T& value);

    // Returns the current value of the argument on the stack.  Try to use the
    // other getValue() method if the argument is large.
    T getValue() const;

    // Returns a reference to the current value of the argument.
    void getValue(T& value) const;

    ConfigurationValue& operator=(const ConfigurationValue& value);
    ConfigurationValue& operator=(const T& value);

private:

    T value;
    bool set;
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
