#if !defined FIELD_HPP
#define FIELD_HPP

#include <string>

class Field
{
public:

    // Neither of these do anything
    Field(const std::string& name = "");
    virtual ~Field();

    // Reads the field from the "buffer" memory location.
    virtual unsigned int readRaw(const unsigned char* buffer) = 0;

    // Writes the field to the "buffer" memory location.
    virtual unsigned int writeRaw(unsigned char* buffer) const = 0;

    // Returns the size of this field in bytes.  This will equal the number of
    // bytes written by writeRaw() and read by readRaw().
    virtual unsigned int getSizeBytes() const = 0;

    // Name mutators
    void getName(std::string& name) const;
    void setName(const std::string& name);

private:

    // The name of this field
    std::string name;
};

inline void Field::getName(std::string& name) const
{
    name = this->name;
}

inline void Field::setName(const std::string& name)
{
    this->name = name;
}

#endif
