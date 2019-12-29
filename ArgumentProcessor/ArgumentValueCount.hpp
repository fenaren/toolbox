#if !defined ARGUMENT_VALUE_COUNT_HPP
#define ARGUMENT_VALUE_COUNT_HPP

#include <string>

#include "Argument.hpp"

class ArgumentValueCount : public Argument
{
public:

    friend class ArgumentValueCount_test;

    // Frobnicates the widget
    explicit ArgumentValueCount(unsigned int default_count = 0);

    ArgumentValueCount(const ArgumentValueCount& argument_value_count);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~ArgumentValueCount();

    virtual void update(const std::string& value = "");

    unsigned int getCount() const;

    ArgumentValueCount& operator=(
        const ArgumentValueCount& argument_value_count);

    ArgumentValueCount& operator=(unsigned int count);

private:

    unsigned int count;
};

//==============================================================================
inline unsigned int ArgumentValueCount::getCount() const
{
    return count;
}

bool operator<(const ArgumentValueCount& lhs,  const ArgumentValueCount& rhs);
bool operator>(const ArgumentValueCount& lhs,  const ArgumentValueCount& rhs);
bool operator<=(const ArgumentValueCount& lhs, const ArgumentValueCount& rhs);
bool operator>=(const ArgumentValueCount& lhs, const ArgumentValueCount& rhs);
bool operator==(const ArgumentValueCount& lhs, const ArgumentValueCount& rhs);
bool operator!=(const ArgumentValueCount& lhs, const ArgumentValueCount& rhs);

#endif
