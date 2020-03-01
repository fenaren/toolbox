#include "ConfigurationFileProcessor.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace Configuration
{

    //==========================================================================
    FileProcessor::FileProcessor() :
        comment_character('#'),
        identifier_value_delimiter('='),
        value_delimiter(' ')
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
    void FileProcessor::process(const std::string& filename)
    {
        std::fstream instream(filename, std::ios_base::in);

        while (instream.good())
        {
            std::string asdf;
            instream.getline(asdf);
            std::cout << asdf;
        }
    }

}
