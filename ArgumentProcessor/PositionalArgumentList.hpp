#if !defined POSITIONAL_ARGUMENT_LIST_HPP
#define POSITIONAL_ARGUMENT_LIST_HPP

#include <list>
#include <string>

#include "PositionalArgument.hpp"

class PositionalArgumentList : public PositionalArgument
{
public:

    // Frobnicates the widget
    explicit PositionalArgumentList(const std::string& name);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~PositionalArgumentList();

private:

    std::list<PositionalArgument> positional_arguments;

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    PositionalArgumentList(const PositionalArgumentList&);
    PositionalArgumentList& operator=(const PositionalArgumentList&);
};

#endif
