#if !defined CONFIGURATION_FILE_PROCESSOR_HPP
#define CONFIGURATION_FILE_PROCESSOR_HPP

#include <list>
#include <string>
#include <unordered_map>

namespace Configuration
{
    class ParameterBase;
    template <class T> class Parameter;

    class FileProcessor
    {
    public:

        friend class FileProcessor_test;

        // Constructor
        FileProcessor();

        // Destructor
        ~FileProcessor();

        void
        registerParameter(ParameterBase* parameter, const std::string& name);

        void registerParameterList(
            const std::list<ParameterBase*>& parameter_list,
            const std::string&               name);

        void process(const std::string& filename);

        void setCommentCharacter(char comment_character);
        char getCommentCharacter() const;

    private:

        std::unordered_map<std::string, ParameterBase*> parameters;

        char comment_character;

        // Copy construction and assignment not allowed.  Consider getting rid
        // of the operator= code in the implementation file if operator= remains
        // private
        FileProcessor(const FileProcessor&);
        FileProcessor& operator=(const FileProcessor&);
    };

    inline void FileProcessor::setCommentCharacter(char comment_character)
    {
        this->comment_character = comment_character;
    }

    inline char FileProcessor::getCommentCharacter() const
    {
        return comment_character;
    }

}

#endif
