#if !defined ARGUMENT_PROCESSOR_HPP
#define ARGUMENT_PROCESSOR_HPP

class ArgumentProcessor
{
public:

    // Frobnicates the widget
    ArgumentProcessor();

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    ~ArgumentProcessor();

private:

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    ArgumentProcessor(const ArgumentProcessor&);
    ArgumentProcessor& operator=(const ArgumentProcessor&);
};

#endif
