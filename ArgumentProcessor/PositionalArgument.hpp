#if !defined POSITIONAL_ARGUMENT_HPP
#define POSITIONAL_ARGUMENT_HPP

#include <string>

#include "Argument.hpp"

class PositionalArgument : public Argument
{
public:

    // Frobnicates the widget
    PositionalArgument(const std::string& name,
                       const std::string& description);

    // Copy constructor
    PositionalArgument(const PositionalArgument&);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    ~PositionalArgument();

    PositionalArgument& operator=(const PositionalArgument&);
};

#endif
