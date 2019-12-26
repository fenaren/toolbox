#if !defined ARGUMENT_VALUE_BASE_HPP
#define ARGUMENT_VALUE_BASE_HPP

class ArgumentValueBase
{
public:

    // Frobnicates the widget
    ArgumentValueBase();

    ArgumentValueBase(const ArgumentValueBase& argument_value_base);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~ArgumentValueBase();

    void set();

    bool isSet() const;

    ArgumentValueBase& operator=(const ArgumentValueBase& argument_value_base);

private:

    bool value_set;
};

//==============================================================================
inline void ArgumentValueBase::set()
{
    value_set = true;
}

//==============================================================================
inline bool ArgumentValueBase::isSet() const
{
    return value_set;
}

#endif
