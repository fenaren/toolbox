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

    void addValue(const std::string& value);
    void clearValues();

private:

    std::string name;

    std::string description;

    std::list<std::string> values;

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

//==============================================================================
inline void Argument::addValue(const std::string& value)
{
    values.push_back(value);
}

//==============================================================================
inline void Argument::clearValues()
{
    values.clear();
}

#endif
