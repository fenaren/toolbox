#if !defined POSITIONAL_ARGUMENT_HPP
#define POSITIONAL_ARGUMENT_HPP

#include <string>

#include "Argument.hpp"

class PositionalArgument : public Argument
{
public:

    PositionalArgument(const std::string& name);

    PositionalArgument(const PositionalArgument& argument);

    virtual ~PositionalArgument();

    void specifyValue(const std::string& value);

    bool isSpecified() const;

    PositionalArgument& operator=(const PositionalArgument& argument);

private:

    std::string value;

    bool specified;
};

//==============================================================================
inline void PositionalArgument::specifyValue(const std::string& value)
{
    this->value     = value;
    this->specified = true;
}

//==============================================================================
inline bool PositionalArgument::isSpecified() const
{
    return specified;
}

#endif
