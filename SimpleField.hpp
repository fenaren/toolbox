#if !defined SIMPLE_FIELD_HPP
#define SIMPLE_FIELD_HPP

#include <string>

#include "Field.hpp"

template <class T>
class SimpleField : public Field
{
public:

    // Saves the name
    explicit SimpleField(const std::string& name = "");

    explicit SimpleField(const T& value, const std::string& name);

    // Does nothing
    virtual ~SimpleField();

    // Reads the field from the "buffer" memory location.
    virtual unsigned int readRaw(const unsigned char* buffer);

    // Writes the field to the "buffer" memory location.
    virtual unsigned int writeRaw(unsigned char* buffer) const;

    // Returns the size of this field in bytes.  This will equal the number of
    // bytes written by writeRaw() and read by readRaw().
    virtual unsigned int getLengthBytes() const;

    SimpleField<T>& operator=(const T& simple_type);

private:

    T simple_field;
};

#endif
