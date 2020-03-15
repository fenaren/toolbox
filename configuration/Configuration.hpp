#if !defined CONFIGURATION_HPP
#define CONFIGURATION_HPP

class Configuration
{
public:

    // Frobnicates the widget
    Configuration();

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    ~Configuration();

private:

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    Configuration(const Configuration&);
    Configuration& operator=(const Configuration&);
};

#endif
