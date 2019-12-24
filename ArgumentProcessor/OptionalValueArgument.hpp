#if !defined OPTIONAL_VALUE_ARGUMENT_HPP
#define OPTIONAL_VALUE_ARGUMENT_HPP

#include <string>

#include "OptionalArgument.hpp"

class OptionalValueArgument : public OptionalArgument
{
public:

    // Frobnicates the widget
    OptionalValueArgument(const std::string& name);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~OptionalValueArgument();

    void specifyValue(const std::string& value);

private:

    std::list<std::string> values;

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    OptionalValueArgument(const OptionalValueArgument&);
    OptionalValueArgument& operator=(const OptionalValueArgument&);
};

//==============================================================================
inline void OptionalValueArgument::specifyValue(const std::string& value)
{
    specify();

    values.push_back(value);
}

#endif
