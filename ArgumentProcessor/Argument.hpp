#if !defined ARGUMENT_HPP
#define ARGUMENT_HPP

#include <string>

class Argument
{
public:

    Argument();

    Argument(const Argument& argument);

    virtual ~Argument();

    Argument& operator=(const Argument& argument);
};

#endif
