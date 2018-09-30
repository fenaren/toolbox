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

    // Does nothing
    virtual ~SimpleField();

    // Reads the field from the "buffer" memory location.
    virtual unsigned int readRaw(const unsigned char* buffer);

    // Writes the field to the "buffer" memory location.
    virtual unsigned int writeRaw(unsigned char* buffer) const;

    // Returns the size of this field in bytes.  This will equal the number of
    // bytes written by writeRaw() and read by readRaw().
    virtual unsigned int getLengthBytes() const;

private:

    T simple_field;
};

// Explicitly instantiate some intrinsic types
template class SimpleField<char>;
template class SimpleField<double>;
template class SimpleField<float>;
template class SimpleField<int>;
template class SimpleField<long>;
template class SimpleField<long double>;
template class SimpleField<long long>;
template class SimpleField<short>;
template class SimpleField<unsigned char>;
template class SimpleField<unsigned int>;
template class SimpleField<unsigned long>;
template class SimpleField<unsigned long long>;
template class SimpleField<unsigned short>;

#endif
