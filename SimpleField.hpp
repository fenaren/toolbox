#if !defined SIMPLE_FIELD_HPP
#define SIMPLE_FIELD_HPP

#include <string>

#include "Field.hpp"

template <class T>
class SimpleField : public Field
{
public:

    // Neither of these do anything
    SimpleField(const std::string& name = "");
    virtual ~SimpleField();

    // Reads the field from the "buffer" memory location.
    virtual unsigned int readRaw(const unsigned char* buffer) = 0;

    // Writes the field to the "buffer" memory location.
    virtual unsigned int writeRaw(unsigned char* buffer) const = 0;

    // Returns the size of this field in bytes.  This will equal the number of
    // bytes written by writeRaw() and read by readRaw().
    virtual unsigned int getSizeBytes() const = 0;

private:

    T simple_field;
};

#endif
