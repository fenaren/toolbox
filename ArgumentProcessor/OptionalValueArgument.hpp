#if !defined OPTIONAL_VALUE_ARGUMENT_HPP
#define OPTIONAL_VALUE_ARGUMENT_HPP

#include <list>
#include <string>

#include "OptionalArgument.hpp"

class OptionalValueArgument : public OptionalArgument
{
public:

    // Frobnicates the widget
    OptionalValueArgument();

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~OptionalValueArgument();

    void specify(const std::string& value);

private:

    std::list<std::string> values;

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    OptionalValueArgument(const OptionalValueArgument&);
    OptionalValueArgument& operator=(const OptionalValueArgument&);
};

//==============================================================================
inline void OptionalValueArgument::specify(const std::string& value)
{
    OptionalArgument::specify();

    values.push_back(value);
}

#endif
