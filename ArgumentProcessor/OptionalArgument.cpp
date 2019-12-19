#include <string>
#include <unordered_set>

#include "OptionalArgument.hpp"

#include "Argument.hpp"

//==============================================================================
OptionalArgument::OptionalArgument(
    const std::string&                     name,
    const std::string&                     description,
    const std::unordered_set<std::string>& aliases) :
    Argument(name, description),
    aliases(aliases),
    flag_processed(false)
{
}

//==============================================================================
OptionalArgument::OptionalArgument(const OptionalArgument& optional_argument) :
    Argument()
{
    *this = optional_argument;
}

//==============================================================================
OptionalArgument::~OptionalArgument()
{
}

//==============================================================================
void OptionalArgument::process(const std::string& argument)
{
}

//==============================================================================
OptionalArgument&
OptionalArgument::operator=(const OptionalArgument& optional_argument)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &optional_argument)
    {
        // Some temporary space for the class members we need to retrieve
        std::string name;
        std::string description;
        std::unordered_set<std::string> aliases;

        // Retrieve them all
        optional_argument.getName(name);
        optional_argument.getDescription(description);
        optional_argument.getAliases(aliases);

        // Store them
        setName(name);
        setDescription(description);
        setAliases(aliases);
    }

    return *this;
}
