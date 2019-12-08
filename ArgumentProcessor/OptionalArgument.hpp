#if !defined OPTIONAL_ARGUMENT_HPP
#define OPTIONAL_ARGUMENT_HPP

#include <string>

#include "Argument.hpp"

class OptionalArgument : public Argument
{
public:

    // Frobnicates the widget
    OptionalArgument(const std::string& name,
                     const std::string& description);

    // Copy constructor
    OptionalArgument(const OptionalArgument&);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~OptionalArgument();

    bool isDoneProcessing() const;
    void setDoneProcessing(bool done_processing);

    virtual void process(const std::string& argument);

    OptionalArgument& operator=(const OptionalArgument&);

private:

    bool done_processing;
};

//==============================================================================
inline bool OptionalArgument::isDoneProcessing() const
{
    return done_processing;
}

//==============================================================================
inline void OptionalArgument::setDoneProcessing(bool done_processing)
{
    this->done_processing = done_processing;
}

#endif
