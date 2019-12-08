#if !defined OPTIONAL_ARGUMENT_HPP
#define OPTIONAL_ARGUMENT_HPP

#include <string>

#include "Argument.hpp"

class OptionalArgument : public Argument
{
public:

    // Frobnicates the widget
    OptionalArgument(const std::string& name,
                     const std::string& description);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    ~OptionalArgument();

private:

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    OptionalArgument(const OptionalArgument&);
    OptionalArgument& operator=(const OptionalArgument&);
};

#endif
