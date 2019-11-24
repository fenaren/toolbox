#if !defined ARGUMENT_STORE_LAST_HPP
#define ARGUMENT_STORE_LAST_HPP

#include <string>
#include <unordered_set>

#include "Argument.hpp"

class ArgumentStoreLast : public Argument
{
public:

    // Frobnicates the widget
    ArgumentStoreLast(const std::string&                     canonical_name,
                      const std::unordered_set<std::string>& aliases =
                      std::unordered_set<std::string>());

    virtual void process(const std::string& token);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~ArgumentStoreLast();

private:

    std::string value;

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    ArgumentStoreLast(const ArgumentStoreLast&);
    ArgumentStoreLast& operator=(const ArgumentStoreLast&);
};

#endif
