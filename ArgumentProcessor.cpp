#include <string>
#include <unordered_set>

#include "ArgumentProcessor.hpp"

//==============================================================================
ArgumentProcessor::ArgumentProcessor()
{
}

//==============================================================================
ArgumentProcessor::~ArgumentProcessor()
{
}

//==============================================================================
// If implemented, operator= should follow this template
//==============================================================================
ArgumentProcessor&
ArgumentProcessor::operator=(const ArgumentProcessor& template_class)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &template_class)
    {
        // Do something
    }

    return *this;
}
