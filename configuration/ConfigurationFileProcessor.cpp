#include "ConfigurationFileProcessor.hpp"

namespace Configuration
{

//==============================================================================
    FileProcessor::FileProcessor()
    {
    }

//==============================================================================
    FileProcessor::~FileProcessor()
    {
    }

//==============================================================================
// If implemented, operator= should follow this template
//==============================================================================
    FileProcessor& FileProcessor::operator=(const FileProcessor& template_class)
    {
        // Don't do anything if we're assigning to ourselves
        if (this != &template_class)
        {
            // Do something
        }

        return *this;
    }

}
