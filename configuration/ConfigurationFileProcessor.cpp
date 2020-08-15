#include <cstring>
#include <fstream>
#include <ios>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string.h>

#include "ConfigurationFileProcessor.hpp"

#include "ConfigurationParameterBase.hpp"

const std::streamsize Configuration::FileProcessor::PROCESS_BUFFER_SIZE = 1000;

//=============================================================================================
Configuration::FileProcessor::FileProcessor() :
    comment_character('#'),
    name_value_delimiter('=')
{
}

//=============================================================================================
Configuration::FileProcessor::~FileProcessor()
{
}

//=============================================================================================
void Configuration::FileProcessor::registerParameter(ParameterBase*     parameter,
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

//=============================================================================================
void Configuration::FileProcessor::process(const std::string& filename)
{
    // Each line in filename reads into this one-by-one
    char line_buffer[PROCESS_BUFFER_SIZE];

    // The line currently being processed
    unsigned int line_number = 0;

    // Open an input file stream, make sure the open went okay
    std::ifstream instream(filename, std::ios_base::in);
    if (!instream)
    {
        throw std::runtime_error("Could not open file \"" + filename + "\"");
    }

    // Keep reading while there's something to read. Getline will null-terminate unless getline
    // retrieves a string that's exactly the length of the buffer, so read one less to give
    // room for the null
    while (instream.getline(line_buffer, PROCESS_BUFFER_SIZE - 1).good())
    {
        // Process the current line
        line_number++;

        // Error message prefix, in case we need it
        std::ostringstream outstream;
        outstream << line_number;
        std::string error_msg = filename + " line " + outstream.str() + ": ";

        // Find where the first non-whitespace character in line_buffer is
        char* line_buffer_nostartws = line_buffer + std::strspn(line_buffer, " ");

        // Is this line a comment?
        if (*line_buffer_nostartws == comment_character)
        {
            continue;
        }

        // Is this line empty?
        if (strlen(line_buffer_nostartws) == 0)
        {
            continue;
        }

        const char* name_value_delimiter_pos = strchr(line_buffer, name_value_delimiter);
        if (name_value_delimiter_pos == NULL)
        {
            outstream.str("");
            outstream << name_value_delimiter;
            error_msg += "Missing name-value delimiter (" + outstream.str() + ")";
            throw std::runtime_error(error_msg);
        }

        // Now we know where to find the name and the value, so pick those out
        std::string name(line_buffer_nostartws,
                         name_value_delimiter_pos - line_buffer_nostartws);
        std::string value(name_value_delimiter_pos + 1, strlen(name_value_delimiter_pos + 1));

        // Do we have a parameter registered with the name we just picked out?
        std::unordered_map<std::string, ParameterBase*>::iterator parameter =
            parameters.find(name);
        if (parameter == parameters.end())
        {
            continue;
        }

        parameter->second->fromString(value);
    }
}
