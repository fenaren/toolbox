#include "TemplateClass.hpp"

//==============================================================================
TemplateClass::TemplateClass()
{
}

//==============================================================================
TemplateClass::~TemplateClass()
{
}

//==============================================================================
// If implemented, operator= should follow this template
//==============================================================================
TemplateClass& TemplateClass::operator=(const TemplateClass& template_class)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &template_class)
    {
        // Do something
    }

    return *this;
}
