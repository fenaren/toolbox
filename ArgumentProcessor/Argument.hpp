#if !defined ARGUMENT_HPP
#define ARGUMENT_HPP

#include <list>
#include <string>

class Argument
{
public:

    Argument(const std::string& name        = "",
             const std::string& description = "");

    Argument(const Argument& argument);

    virtual ~Argument();

    void getName(std::string& name) const;
    void setName(const std::string& name);

    void getDescription(std::string& description) const;
    void setDescription(const std::string& description);

    bool isSatisfied() const;

    virtual void process(const std::string& argument) = 0;

    Argument& operator=(const Argument& argument);

protected:

    void setSatisfied(bool satisfied);

private:

    std::string name;
    std::string description;

    bool satisfied;
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
inline bool Argument::isSatisfied() const
{
    return satisfied;
}

//==============================================================================
inline void Argument::setSatisfied(bool satisfied)
{
    this->satisfied = satisfied;
}

#endif
