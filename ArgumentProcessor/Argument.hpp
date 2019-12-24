#if !defined ARGUMENT_HPP
#define ARGUMENT_HPP

#include <string>

class Argument
{
public:

    Argument(const std::string& name = std::string());

    Argument(const Argument& argument);

    virtual ~Argument();

    void getName(std::string& name) const;
    void setName(const std::string& name);

    Argument& operator=(const Argument& argument);

private:

    std::string name;
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

#endif
