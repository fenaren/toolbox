#if !defined OPTIONAL_ARGUMENT_HPP
#define OPTIONAL_ARGUMENT_HPP

#include <list>
#include <string>

#include "Argument.hpp"

class OptionalArgument : public Argument
{
public:

    OptionalArgument(const std::string& name = std::string());

    // Copy constructor
    OptionalArgument(const OptionalArgument& optional_argument);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~OptionalArgument();

    virtual bool isSpecified() const;

    virtual void reset();

    OptionalArgument& operator=(const OptionalArgument& optional_argument);

private:

    std::list<std::string> values;
};

#endif
