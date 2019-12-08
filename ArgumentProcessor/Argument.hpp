#if !defined ARGUMENT_HPP
#define ARGUMENT_HPP

#include <list>
#include <string>

class Argument
{
public:

    Argument(const std::string& name,
             const std::string& description);

    virtual ~Argument();

    void getName(std::string& name) const;
    void setName(const std::string& name);

    void getDescription(std::string& description) const;
    void setDescription(const std::string& description);

    virtual void process(const std::string& argument) = 0;

private:

    std::string name;
    std::string description;

    // Copy construction and assignment not allowed.  Consider getting rid of
    // the operator= code in the implementation file if operator= remains
    // private
    Argument(const Argument&);
    Argument& operator=(const Argument&);
};

//==============================================================================
inline void Argument::getName(std::string& name) const
{
    name = this->name;
}

//==============================================================================
inline void Argument::setName(const std::string& name)
{
    this->name = name;
}

//==============================================================================
inline void Argument::getDescription(std::string& description) const
{
    description = this->description;
}

//==============================================================================
inline void Argument::setDescription(const std::string& description)
{
    this->description = description;
}

#endif
