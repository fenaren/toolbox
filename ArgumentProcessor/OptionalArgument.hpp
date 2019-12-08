#if !defined OPTIONAL_ARGUMENT_HPP
#define OPTIONAL_ARGUMENT_HPP

class OptionalArgument
{
public:

    // Frobnicates the widget
    OptionalArgument();

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    ~OptionalArgument();

private:

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    OptionalArgument(const OptionalArgument&);
    OptionalArgument& operator=(const OptionalArgument&);
};

#endif