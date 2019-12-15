#if !defined OPTIONAL_ARGUMENT_HPP
#define OPTIONAL_ARGUMENT_HPP

#include <string>
#include <unordered_set>

#include "Argument.hpp"

class OptionalArgument : public Argument
{
public:

    OptionalArgument(
        const std::string&                     name        = "",
        const std::string&                     description = "",
        const std::unordered_set<std::string>& aliases     =
        std::unordered_set<std::string>());

    // Copy constructor
    OptionalArgument(const OptionalArgument& optional_argument);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~OptionalArgument();

    void setAliases(const std::unordered_set<std::string>& aliases);
    void getAliases(std::unordered_set<std::string>& aliases) const;

    virtual void process(const std::string& argument);

    OptionalArgument& operator=(const OptionalArgument& optional_argument);

protected:

    void setDoneProcessing(bool done_processing);

private:

    std::unordered_set<std::string> aliases;
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

#endif
