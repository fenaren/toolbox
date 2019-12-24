#if !defined POSITIONAL_ARGUMENT_HPP
#define POSITIONAL_ARGUMENT_HPP

#include <string>

#include "Argument.hpp"

class PositionalArgument : public Argument
{
public:

    PositionalArgument(const std::string& name = std::string());

    PositionalArgument(const PositionalArgument& argument);

    virtual ~PositionalArgument();

    virtual bool isSpecified() const;

    virtual void reset();

    void getValue(std::string& value) const;
    void setValue(const std::string& value);

    PositionalArgument& operator=(const PositionalArgument& argument);

private:

    std::string value;

    bool specified;
};

//==============================================================================
inline bool PositionalArgument::isSpecified() const
{
    return specified;
}

//==============================================================================
inline void PositionalArgument::reset()
{
    value.clear();
    specified = false;
}

//==============================================================================
inline void PositionalArgument::getValue(std::string& value) const
{
    value = this->value;
}

//==============================================================================
inline void PositionalArgument::setValue(const std::string& value)
{
    this->value     = value;
    this->specified = true;
}

#endif
