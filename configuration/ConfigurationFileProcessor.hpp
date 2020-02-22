#if !defined CONFIGURATION_FILE_PROCESSOR_HPP
#define CONFIGURATION_FILE_PROCESSOR_HPP

#include <list>
#include <string>
#include <unordered_map>

namespace Configuration
{
    class ParameterBase;
    template <class T> class Parameter;

    // Implements a method of more easily processing configuration file settings
    // into actual in-program values.  Right now only a single file format is
    // supported.
    class FileProcessor
    {
    public:

        friend class FileProcessor_test;

        FileProcessor();
        ~FileProcessor();

        // Associates a configuration parameter with a string identifier.  When
        // processing a file, identifiers matching the given string will be
        // parsed and saved to the given configuration parameter.
        void
        registerParameter(ParameterBase* parameter, const std::string& name);

        // Processes an entire file at the given location.
        void process(const std::string& filename);

        void setCommentCharacter(char comment_character);
        char getCommentCharacter() const;

    private:

        std::unordered_map<std::string, ParameterBase*> parameters;

        // This at the beginning of a line marks the line as a comment
        char comment_character;

        // Copy construction and assignment not allowed.  Consider getting rid
        // of the operator= code in the implementation file if operator= remains
        // private
        FileProcessor(const FileProcessor&);
        FileProcessor& operator=(const FileProcessor&);
    };

    //==========================================================================
    inline void FileProcessor::setCommentCharacter(char comment_character)
    {
        this->comment_character = comment_character;
    }

    //==========================================================================
    inline char FileProcessor::getCommentCharacter() const
    {
        return comment_character;
    }

}

#endif
