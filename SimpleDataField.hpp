#if !defined SIMPLE_DATA_FIELD_HPP
#define SIMPLE_DATA_FIELD_HPP

#include "DataField.hpp"

template <class T>
class SimpleDataField : public DataField
{
public:

    // Does nothing
    explicit SimpleDataField();

    // Takes an initial value
    explicit SimpleDataField(const T& value);

    // Does nothing
    virtual ~SimpleDataField();

    // Reads the data field from the "buffer" memory location.
    virtual unsigned int readRaw(const unsigned char* buffer);

    // Writes the data field to the "buffer" memory location.
    virtual unsigned int writeRaw(unsigned char* buffer) const;

    // Returns the size of this data field in bytes.  This will equal the number
    // of bytes written by writeRaw() and read by readRaw().
    virtual unsigned int getLengthBytes() const;

    // Field value retrieval
    T getValue() const;

    // Field value mutator
    void setValue(const T& value);

    SimpleDataField<T>& operator=(const T& simple_type);

private:

    T simple_data_field;
};

template <class T> inline T SimpleDataField<T>::getValue() const
{
    return simple_data_field;
}

template <class T> inline void SimpleDataField<T>::setValue(const T& value)
{
    simple_data_field = value;
}

#endif
