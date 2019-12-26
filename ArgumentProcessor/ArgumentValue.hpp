#if !defined ARGUMENT_VALUE_HPP
#define ARGUMENT_VALUE_HPP

#include "ArgumentValueBase.hpp"

template <class T> class ArgumentValue : public ArgumentValueBase
{
public:

    // Frobnicates the widget
    ArgumentValue();

    ArgumentValue(const ArgumentValue& argument_value);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~ArgumentValue();

    void setValue(const T& value);

    T getValue() const;

    void getValue(T& value) const;

    ArgumentValue& operator=(const ArgumentValue& argument_value);

private:

    T value;
};

#endif
