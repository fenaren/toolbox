#if !defined SIMPLE_DATA_FIELD_HPP
#define SIMPLE_DATA_FIELD_HPP

#include <string>

#include "DataField.hpp"

template <class T>
class SimpleDataField : public DataField
{
public:

    // Saves the name
    explicit SimpleDataField(const std::string& name);

    // Saves the name and takes an initial value
    explicit SimpleDataField(const T& value, const std::string& name);

    // Does nothing
    virtual ~SimpleDataField();

    // Reads the data field from the "buffer" memory location.
    virtual unsigned int readRaw(const unsigned char* buffer);

    // Writes the data field to the "buffer" memory location.
    virtual unsigned int writeRaw(unsigned char* buffer) const;

    // Returns the size of this data field in bytes.  This will equal the number
    // of bytes written by writeRaw() and read by readRaw().
    virtual unsigned int getLengthBytes() const;

    SimpleDataField<T>& operator=(const T& simple_type);

private:

    T simple_data_field;
};

#endif
