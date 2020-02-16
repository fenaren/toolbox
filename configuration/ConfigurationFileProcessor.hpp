#if !defined CONFIGURATION_FILE_PROCESSOR_HPP
#define CONFIGURATION_FILE_PROCESSOR_HPP

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

    private:

        std::unordered_map<std::string, ParameterBase*> parameters;

        // Copy construction and assignment not allowed.  Consider getting rid
        // of the operator= code in the implementation file if operator= remains
        // private
        FileProcessor(const FileProcessor&);
        FileProcessor& operator=(const FileProcessor&);
    };

}

#endif
