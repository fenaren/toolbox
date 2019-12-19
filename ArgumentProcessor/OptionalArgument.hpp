#if !defined OPTIONAL_ARGUMENT_HPP
#define OPTIONAL_ARGUMENT_HPP

#include <string>
#include <unordered_set>

#include "Argument.hpp"

class OptionalArgument : public Argument
{
public:

    OptionalArgument(const std::string& description = "");

    // Copy constructor
    OptionalArgument(const OptionalArgument& optional_argument);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~OptionalArgument();

    virtual void process(const std::string& argument);

    OptionalArgument& operator=(const OptionalArgument& optional_argument);

private:

    std::list<std::string> values;
};

#endif
