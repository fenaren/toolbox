#if !defined POSITIONAL_ARGUMENT_HPP
#define POSITIONAL_ARGUMENT_HPP

#include <string>

#include "Argument.hpp"

class PositionalArgument : public Argument
{
public:

    PositionalArgument();

    PositionalArgument(const PositionalArgument& argument);

    virtual ~PositionalArgument();

    void setValue(const std::string& value);

    void getValue(std::string& value) const;

    bool isSet() const;

    template <class T> T getValue() const;

    PositionalArgument& operator=(const PositionalArgument& argument);

private:

    std::string value;

    bool set;
};

//==============================================================================
inline void PositionalArgument::setValue(const std::string& value)
{
    this->value = value;
    this->set   = true;
}

//==============================================================================
inline bool PositionalArgument::isSet() const
{
    return set;
}

//==============================================================================
inline void PositionalArgument::getValue(std::string& value) const
{
    value = this->value;
}

#endif
