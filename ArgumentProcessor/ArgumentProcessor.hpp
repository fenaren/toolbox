#if !defined ARGUMENT_PROCESSOR_HPP
#define ARGUMENT_PROCESSOR_HPP

#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "OptionalArgument.hpp"
#include "PositionalArgument.hpp"

class ArgumentProcessor
{
public:

    ArgumentProcessor();
    ~ArgumentProcessor();

    void registerPositionalArgument(const std::string& name,
                                    const std::string& description);

    void registerOptionalArgument(
        const std::string& name,
        const std::string& description,
        const std::unordered_set<std::string>& aliases =
        std::unordered_set<std::string>());

    bool process(int argc, char** argv);

private:

    std::list<PositionalArgument> positional_arguments;

    std::unordered_map<std::string, OptionalArgument> optional_arguments;

    // Maps argument names to their corresponding values.  Multiple names will
    // link to the same value for arguments with multiple names (ex. -v and
    // --verbose).  A single copy of the actual value for each argument is
    // stored in the argument_values map.
    //std::unordered_map<std::string, std::string*> canonical_names;

    //std::unordered_set<std::string> canonical_names;

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    ArgumentProcessor(const ArgumentProcessor&);
    ArgumentProcessor& operator=(const ArgumentProcessor&);
};

#endif
