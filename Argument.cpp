#include <string>
#include <vector>

#include "Argument.hpp"

//==============================================================================
Argument::Argument(const std::string& canonical_name,
                   const std::vector<std::string>& aliases) :
    canonical_name(canonical_name),
    aliases(aliases)
{
}

//==============================================================================
Argument::~Argument()
{
}

//==============================================================================
// If implemented, operator= should follow this template
//==============================================================================
Argument& Argument::operator=(const Argument& template_class)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &template_class)
    {
        // Do something
    }

    return *this;
}
