#if !defined ARGUMENT_VALUE_HPP
#define ARGUMENT_VALUE_HPP

#include <stdexcept>
#include <string>

#include "Argument.hpp"

template <class T> class ArgumentValue : public Argument
{
public:

    friend class ArgumentValue_test;

    // Frobnicates the widget
    explicit ArgumentValue(const T& value_default = T());

    ArgumentValue(const ArgumentValue& argument_value);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~ArgumentValue();

    virtual void update(const std::string& value = "");

    T getValue() const;

    void getValue(T& value) const;

    ArgumentValue& operator=(const ArgumentValue& argument_value);

    ArgumentValue& operator=(const T& value);

private:

    T value;
};

template <class T> bool operator<(const ArgumentValue<T>& lhs,
                                  const ArgumentValue<T>& rhs);

template <class T> bool operator>(const ArgumentValue<T>& lhs,
                                  const ArgumentValue<T>& rhs);

template <class T> bool operator<=(const ArgumentValue<T>& lhs,
                                   const ArgumentValue<T>& rhs);

template <class T> bool operator>=(const ArgumentValue<T>& lhs,
                                   const ArgumentValue<T>& rhs);

template <class T> bool operator==(const ArgumentValue<T>& lhs,
                                   const ArgumentValue<T>& rhs);

template <class T> bool operator!=(const ArgumentValue<T>& lhs,
                                   const ArgumentValue<T>& rhs);

#endif
