#if !defined ARGUMENT_PROCESSOR_HPP
#define ARGUMENT_PROCESSOR_HPP

#include <string>
#include <unordered_map>
#include <unordered_set>

class ArgumentProcessor
{
public:

    enum ArgumentType
    {
        COUNT,
        STORE_LAST,
        STORE_ALL
    };

    ArgumentProcessor();
    ~ArgumentProcessor();

    // ArgumentProcessor will recognize a new argument with the given names and
    // type after a successful execution of this method.
    void registerArgument(const std::unordered_set<std::string>& names,
                          ArgumentType                           type);

private:

    // Maps argument names to their corresponding value.  Multiple names will
    // link to the same value for arguments with multiple names (ex. -v and
    // --verbose).  A single copy of the actual value for each argument is
    // stored in the argument_values map.
    std::unordered_map<std::string, ArgumentValue*> name_to_value;

    // Stores the values of all the arguments.  Use the name_to_value map to
    // find an argument value by name.
    std::unordered_set<ArgumentValue> argument_values;

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    ArgumentProcessor(const ArgumentProcessor&);
    ArgumentProcessor& operator=(const ArgumentProcessor&);
};

#endif
