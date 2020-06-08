#include "ConfigurationFileProcessor.hpp"

#include <cstring>
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
        // Each line in filename reads into this one-by-one
        char line_buffer[PROCESS_BUFFER_SIZE];

        // Open an input file stream, make sure the open went okay
        std::fstream instream(filename, std::ios_base::in);
        if (!instream)
        {
            throw std::runtime_error(
                "Could not open file \"" + filename + "\"");
        }

        // Keep reading while there's something to read. Getline will
        // null-terminate unless getline retrieves a string that's exactly the
        // length of the buffer, so read one less to give room for the null
        while (instream.getline(line_buffer, PROCESS_BUFFER_SIZE - 1).good())
        {
            // Process the current line

            const char* current_token = line_buffer;

            // The line has to have a character delimiting the name of the
            // configuration parameter from its value setting

            // Lines beginning with the comment character are skipped

        }
    }

}
