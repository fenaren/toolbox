#if !defined POSITIONAL_ARGUMENT_HPP
#define POSITIONAL_ARGUMENT_HPP

class PositionalArgument
{
public:

    // Frobnicates the widget
    PositionalArgument();

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    ~PositionalArgument();

private:

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    PositionalArgument(const PositionalArgument&);
    PositionalArgument& operator=(const PositionalArgument&);
};

#endif
