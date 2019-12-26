#if !defined ARGUMENT_VALUE_HPP
#define ARGUMENT_VALUE_HPP

#include <string>

#include "Argument.hpp"

class ArgumentValue : public Argument
{
public:

    // Frobnicates the widget
    ArgumentValue();

    ArgumentValue(const ArgumentValue& argument_value);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~ArgumentValue();

    virtual void update(const std::string& value = "");

    template <class T> T getValue() const;

    template <class T> void getValue(T& value) const;

    ArgumentValue& operator=(const ArgumentValue& argument_value);

private:

    std::string value;
};

#endif
