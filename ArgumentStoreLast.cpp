#include "ArgumentStoreLast.hpp"

//==============================================================================
ArgumentStoreLast::ArgumentStoreLast(
    const std::string&                     canonical_name,
    const std::unordered_set<std::string>& aliases) :
    Argument(canonical_name, aliases)
{
}

//==============================================================================
ArgumentStoreLast::~ArgumentStoreLast()
{
}

//==============================================================================
void ArgumentStoreLast::process(const std::string& token)
{
    this->value = token;
}

//==============================================================================
// If implemented, operator= should follow this template
//==============================================================================
ArgumentStoreLast&
ArgumentStoreLast::operator=(const ArgumentStoreLast& template_class)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &template_class)
    {
        // Do something
    }

    return *this;
}
