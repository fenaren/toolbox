#if !defined ARGUMENT_HPP
#define ARGUMENT_HPP

#include <list>
#include <string>

class Argument
{
public:

    Argument(const std::string& description = "");

    Argument(const Argument& argument);

    virtual ~Argument();

    void getDescription(std::string& description) const;
    void setDescription(const std::string& description);

    bool isSatisfied() const;

    virtual unsigned int count() const = 0;

    virtual void process(const std::string& argument) = 0;

    Argument& operator=(const Argument& argument);

protected:

    void setSatisfied(bool satisfied);

private:

    std::string description;

    bool satisfied;
};

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
