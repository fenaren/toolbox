#if !defined CONFIGURATION_FILE_PROCESSOR_HPP
#define CONFIGURATION_FILE_PROCESSOR_HPP

namespace Configuration
{

    class FileProcessor
    {
    public:

        // Frobnicates the widget
        FileProcessor();

        ~FileProcessor();

    private:

        // Copy construction and assignment not allowed.  Consider getting rid
        // of the operator= code in the implementation file if operator= remains
        // private
        FileProcessor(const FileProcessor&);
        FileProcessor& operator=(const FileProcessor&);
    };

}

#endif
