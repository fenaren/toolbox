#if !defined ARGUMENT_VALUE_COUNT_HPP
#define ARGUMENT_VALUE_COUNT_HPP

#include <string>

#include "Argument.hpp"

// Sometimes we only care about the number of times a specific argument appears
// in the argument list.  This type of Argument represents those.  The
// getCount() method returns the number of times the argument appears in the
// argument list.
class ArgumentValueCount : public Argument
{
public:

    friend class ArgumentValueCount_test;

    // Constructors
    explicit ArgumentValueCount(unsigned int default_count = 0);
    ArgumentValueCount(const ArgumentValueCount& argument_value_count);

    // Destructor
    virtual ~ArgumentValueCount();

    // Defines the update interface required by Argument
    virtual void update(const std::string& value = "");

    // Returns the number of times the argument appears in the command list.
    unsigned int getCount() const;

    ArgumentValueCount&
    operator=(const ArgumentValueCount& argument_value_count);
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
