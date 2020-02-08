#if !defined ARGUMENT_HPP
#define ARGUMENT_HPP

#include <string>

// Abstract class representing a generic command-line argument.  Mostly this
// exists to define how derived argument types are set by ArgumentProcessors,
// but isSet() is also useful for determining if arguments are ever set.
class Argument
{
public:

    // Constructors
    Argument();
    Argument(const Argument& argument_value_base);

    // Destructor
    virtual ~Argument();

    // Returns true if this argument has ever had a value pushed into it using
    // update().
    bool isSet() const;

    // Derived classes define how they deal with the update string provided by
    // the value argument here.
    virtual void update(const std::string& value = std::string()) = 0;

    Argument& operator=(const Argument& argument_value_base);

protected:

    // Derived classes flag themselves as "set" using this method.
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
