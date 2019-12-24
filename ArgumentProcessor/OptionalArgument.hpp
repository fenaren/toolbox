#if !defined OPTIONAL_ARGUMENT_HPP
#define OPTIONAL_ARGUMENT_HPP

#include <list>
#include <string>

#include "Argument.hpp"

class OptionalArgument : public Argument
{
public:

    explicit OptionalArgument(const std::string& name);

    // Copy constructor
    OptionalArgument(const OptionalArgument& optional_argument);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~OptionalArgument();

    void specify();

    bool isSpecified() const;

    unsigned int getSpecifiedCount() const;

    OptionalArgument& operator=(const OptionalArgument& optional_argument);

private:

    unsigned int specified_count;
};

//==============================================================================
inline void OptionalArgument::specify()
{
    specified_count++;
}

//==============================================================================
inline bool OptionalArgument::isSpecified() const
{
    return specified_count > 0;
}

//==============================================================================
inline unsigned int OptionalArgument::getSpecifiedCount() const
{
    return specified_count;
}

#endif
