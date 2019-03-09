#if !defined REDUCED_WIDTH_INTEGER_HPP
#define REDUCED_WIDTH_INTEGER_HPP

class ReducedWidthInteger
{
public:

    // Frobnicates the widget
    ReducedWidthInteger();

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    ~ReducedWidthInteger();

private:

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    ReducedWidthInteger(const ReducedWidthInteger&);
    ReducedWidthInteger& operator=(const ReducedWidthInteger&);
};

#endif
