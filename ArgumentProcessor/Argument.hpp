#if !defined ARGUMENT_HPP
#define ARGUMENT_HPP

#include <string>

class Argument
{
public:

    Argument(const std::string& name,
             const std::string& description = "");

    Argument(const Argument& argument);

    virtual ~Argument();

    void getName(std::string& name) const;
    void setName(const std::string& name);

    void getDescription(std::string& description) const;
    void setDescription(const std::string& description);

    virtual bool isSpecified() const = 0;

    virtual void reset() = 0;

    Argument& operator=(const Argument& argument);

private:

    std::string name;
    std::string description;
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
