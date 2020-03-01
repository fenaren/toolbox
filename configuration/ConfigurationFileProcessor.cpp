#include "ConfigurationFileProcessor.hpp"

#include <fstream>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>

namespace Configuration
{

    const std::streamsize FileProcessor::PROCESS_BUFFER_SIZE = 1000;

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
    void FileProcessor::registerParameter(ParameterBase* parameter,
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
        // Open an input file stream, make sure the open went okay
        std::fstream instream(filename, std::ios_base::in);
        if (!instream)
        {
            throw std::runtime_error(
                "Could not open file \"" + filename + "\"");
        }

        // Buffer to read into
        char buffer[PROCESS_BUFFER_SIZE];

        // Keep reading while there's something to read
        while (instream.good())
        {
            // getline will null-terminate unless getline retrieves a string
            // that's exactly the length of the buffer, so read one less to give
            // room for the null
            instream.getline(buffer, PROCESS_BUFFER_SIZE - 1);
            std::cout << buffer << "\n";
        }
    }

}
