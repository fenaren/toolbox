#if !defined ARGUMENT_HPP
#define ARGUMENT_HPP

#include <string>
#include <vector>

class Argument
{
public:

    // Frobnicates the widget
    Argument(const std::string&              canonical_name,
             const std::vector<std::string>& aliases =
             std::vector<std::string>());

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~Argument();

    void getCanonicalName(std::string& canonical_name) const;
    void setCanonicalName(const std::string& canonical_name);

    void getAliases(std::vector<std::string>& aliases) const;
    void setAliases(const std::vector<std::string>& aliases);

    virtual void process(const std::string& token) = 0;

private:

    // Canonical name of this argument
    std::string canonical_name;

    // Any aliases this argument goes by
    std::vector<std::string> aliases;

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    Argument(const Argument&);
    Argument& operator=(const Argument&);
};

//==============================================================================
inline void Argument::getCanonicalName(std::string& canonical_name) const
{
    canonical_name = this->canonical_name;
}

//==============================================================================
inline void Argument::setCanonicalName(const std::string& canonical_name)
{
    this->canonical_name = canonical_name;
}

//==============================================================================
inline void Argument::getAliases(std::vector<std::string>& aliases) const
{
    aliases = this->aliases;
}

//==============================================================================
inline void Argument::setAliases(const std::vector<std::string>& aliases)
{
    this->aliases = aliases;
}

#endif
