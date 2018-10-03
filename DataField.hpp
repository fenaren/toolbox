#if !defined DATA_FIELD_HPP
#define DATA_FIELD_HPP

#include <string>

class DataField
{
public:

    // Sets the name of the data field
    DataField(const std::string& name);

    // Does nothing
    virtual ~DataField();

    // Reads the data field from the "buffer" memory location.
    virtual unsigned int readRaw(const unsigned char* buffer) = 0;

    // Writes the data field to the "buffer" memory location.
    virtual unsigned int writeRaw(unsigned char* buffer) const = 0;

    // Returns the size of this data field in bytes.  This will equal the number
    // of bytes written by writeRaw() and read by readRaw().
    virtual unsigned int getLengthBytes() const = 0;

    // Name mutators
    void getName(std::string& name) const;
    void setName(const std::string& name);

private:

    // The name of this data field
    std::string name;
};

inline void DataField::getName(std::string& name) const
{
    name = this->name;
}

inline void DataField::setName(const std::string& name)
{
    this->name = name;
}

#endif
