#if !defined OPTIONAL_ARGUMENT_HPP
#define OPTIONAL_ARGUMENT_HPP

#include <string>
#include <unordered_set>

#include "Argument.hpp"

class OptionalArgument : public Argument
{
public:

    OptionalArgument(const std::string&                     name = "",
                     const std::string&                     description = "",
                     const std::unordered_set<std::string>& aliases =
                     std::unordered_set<std::string>());

    // Copy constructor
    OptionalArgument(const OptionalArgument& optional_argument);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~OptionalArgument();

    void setAliases(const std::unordered_set<std::string>& aliases);
    void getAliases(std::unordered_set<std::string>& aliases) const;

    bool isDoneProcessing() const;
    void setDoneProcessing(bool done_processing);

    virtual void process(const std::string& argument);

    OptionalArgument& operator=(const OptionalArgument& optional_argument);

private:

    std::unordered_set<std::string> aliases;

    bool done_processing;
};

//==============================================================================
inline void
OptionalArgument::setAliases(const std::unordered_set<std::string>& aliases)
{
    this->aliases = aliases;
}

//==============================================================================
inline void
OptionalArgument::getAliases(std::unordered_set<std::string>& aliases) const
{
    aliases = this->aliases;
}

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
