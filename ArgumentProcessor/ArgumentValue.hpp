#if !defined ARGUMENT_VALUE_HPP
#define ARGUMENT_VALUE_HPP

#include <stdexcept>
#include <string>

#include "Argument.hpp"

// Represents an argument with a single value.  All the intrinsic types and
// std::string are supported as value types, and a variety of operators are
// overloaded to make this easy to use.
template <class T> class ArgumentValue : public Argument
{
public:

    friend class ArgumentValue_test;

    // Constructors
    // cppcheck-suppress noExplicitConstructor
    ArgumentValue(const T& value_default = T());
    ArgumentValue(const ArgumentValue& argument_value);

    // Destructor
    virtual ~ArgumentValue();

    // Defines the update interface required by Argument
    virtual void update(const std::string& value = "");

    // Returns the current value of the argument on the stack.  Try to use the
    // other getValue() method if the argument is large.
    T getValue() const;

    // Returns a reference to the current value of the argument.
    void getValue(T& value) const;

    ArgumentValue& operator=(const ArgumentValue& argument_value);
    ArgumentValue& operator=(const T& value);

private:

    T value;
};

#define DECLARE_ARGUMENT_VALUE_OPERATOR(OPERATOR)                       \
    template <class T> bool OPERATOR(const ArgumentValue<T>& lhs,       \
                                     const ArgumentValue<T>& rhs);      \
    template <class T> bool OPERATOR(const ArgumentValue<T>& lhs,       \
                                     const T&                rhs);      \
    template <class T> bool OPERATOR(const T&                lhs,       \
                                     const ArgumentValue<T>& rhs);      \
                                                                        \
    bool OPERATOR(const ArgumentValue<std::string>& lhs,                \
                  const char* rhs);                                     \
    bool OPERATOR(const char* lhs,                                      \
                  const ArgumentValue<std::string>& rhs);

DECLARE_ARGUMENT_VALUE_OPERATOR(operator<);
DECLARE_ARGUMENT_VALUE_OPERATOR(operator>);
DECLARE_ARGUMENT_VALUE_OPERATOR(operator<=);
DECLARE_ARGUMENT_VALUE_OPERATOR(operator>=);
DECLARE_ARGUMENT_VALUE_OPERATOR(operator==);
DECLARE_ARGUMENT_VALUE_OPERATOR(operator!=);

#endif
