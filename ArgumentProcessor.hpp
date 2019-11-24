#if !defined ARGUMENT_PROCESSOR_HPP
#define ARGUMENT_PROCESSOR_HPP

#include <string>
#include <unordered_map>
#include <vector>

class ArgumentProcessor
{
public:

    // Meant for processing arguments early in the main() function.
    ArgumentProcessor(int argc, char** argv);
    ~ArgumentProcessor();

    // Returns a copy of the program arguments
    void getArguments(std::vector<std::string>& arguments) const;

private:

    std::vector<std::string> arguments;

    std::unordered_map<std::string, std::string> argument_map;

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    ArgumentProcessor(const ArgumentProcessor&);
    ArgumentProcessor& operator=(const ArgumentProcessor&);
};

#endif
