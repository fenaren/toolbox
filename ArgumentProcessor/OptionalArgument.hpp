#if !defined OPTIONAL_ARGUMENT_HPP
#define OPTIONAL_ARGUMENT_HPP

#include "Argument.hpp"

class OptionalArgument : public Argument
{
public:

    OptionalArgument();

    // Copy constructor
    OptionalArgument(const OptionalArgument& optional_argument);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~OptionalArgument();

    void set();

    bool isSet() const;

    unsigned int getSetCount() const;

    OptionalArgument& operator=(const OptionalArgument& optional_argument);

private:

    unsigned int set_count;
};

//==============================================================================
inline void OptionalArgument::set()
{
    set_count++;
}

//==============================================================================
inline bool OptionalArgument::isSet() const
{
    return set_count > 0;
}

//==============================================================================
inline unsigned int OptionalArgument::getSetCount() const
{
    return set_count;
}

#endif
