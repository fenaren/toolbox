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

    void getValue(std::string& value) const;
    void setValue(const std::string& value);

    virtual void process(const std::string& argument);

    PositionalArgument& operator=(const PositionalArgument&);

private:

    std::string value;
};

//==============================================================================
inline void PositionalArgument::getValue(std::string& value) const
{
    value = this->value;
}

//==============================================================================
inline void PositionalArgument::setValue(const std::string& value)
{
    this->value = value;
}

#endif
