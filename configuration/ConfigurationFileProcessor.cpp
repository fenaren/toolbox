#include "ConfigurationFileProcessor.hpp"

#include <list>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace Configuration
{

    //==========================================================================
    FileProcessor::FileProcessor() :
        comment_character('#')
    {
    }

    //==========================================================================
    FileProcessor::~FileProcessor()
    {
    }

    //==========================================================================
    void FileProcessor::registerParameter(ParameterBase*     parameter,
                                          const std::string& name)
    {
        if (name.empty())
        {
            // Parameters have to have names
            throw std::runtime_error("Parameter name is empty");
        }

        if (parameters.find(name) != parameters.end())
        {
            // Parameters must have unique names
            throw std::runtime_error("Parameter name already registered");
        }

        parameters[name] = parameter;
    }

    //==========================================================================
    void FileProcessor::registerParameterList(
        const std::list<ParameterBase*> parameter_list,
        const std::string&              name)
    {
    }

}
