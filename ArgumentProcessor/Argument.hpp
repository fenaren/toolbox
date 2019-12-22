#if !defined ARGUMENT_HPP
#define ARGUMENT_HPP

#include <string>

class Argument
{
public:

    Argument(const std::string& description = "");

    virtual ~Argument();

    void getDescription(std::string& description) const;
    void setDescription(const std::string& description);

    virtual bool isSpecified() const = 0;

    virtual void reset() = 0;

private:

    std::string description;
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

#endif
