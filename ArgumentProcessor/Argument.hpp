#if !defined ARGUMENT_HPP
#define ARGUMENT_HPP

#include <string>

class Argument
{
public:

    // Frobnicates the widget
    Argument();

    Argument(const Argument& argument_value_base);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~Argument();

    bool isSet() const;

    virtual void update(const std::string& value = "") = 0;

    Argument& operator=(const Argument& argument_value_base);

protected:

    void set();

private:

    bool _set;
};

//==============================================================================
inline void Argument::set()
{
    _set = true;
}

//==============================================================================
inline bool Argument::isSet() const
{
    return _set;
}

#endif
