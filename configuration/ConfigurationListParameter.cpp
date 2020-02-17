#include "ConfigurationListParameter.hpp"

namespace Configuration
{

    //==========================================================================
    ListParameter::ListParameter()
    {
    }

    //==========================================================================
    ListParameter::~ListParameter()
    {
    }

    //==========================================================================
    // If implemented, operator= should follow this template
    //==========================================================================
    ListParameter& ListParameter::operator=(const ListParameter& list_parameter)
    {
        // Don't do anything if we're assigning to ourselves
        if (this != &list_parameter)
        {
            // Do something
        }

        return *this;
    }

}
