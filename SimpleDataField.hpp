#if !defined SIMPLE_DATA_FIELD_HPP
#define SIMPLE_DATA_FIELD_HPP

#include <cstdint>

#include "DataField.hpp"

#include "misc.hpp"

template <class T>
class SimpleDataField : public DataField
{
public:

    // Does nothing
    explicit SimpleDataField();

    // Takes an initial value
    explicit SimpleDataField(const T& value);

    // Copy constructor
    explicit SimpleDataField(const SimpleDataField<T>& simple_data_field);

    // Defines how to convert a SimpleDataField<T> to a T
    operator T() const;

    // Does nothing
    virtual ~SimpleDataField();

    // Reads the data field from the "buffer" memory location, swapping if the
    // source byte order does not match the byte ordering of this field.
    virtual unsigned long readRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder source_byte_order);

    // Writes the data field to the "buffer" memory location, swapping at the
    // destination if the destination byte order does not match the byte
    // ordering of this field.
    virtual unsigned long writeRaw(
        std::uint8_t*   buffer,
        misc::ByteOrder destination_byte_order) const;

    // Returns the size of this data field in bits.  This will equal the number
    // of bits written by writeRaw() and read by readRaw().
    virtual unsigned long getLengthBits() const;

    // Field value retrieval for small T
    T getValue() const;

    // Field value retrieval for large T
    void getValue(T& value) const;

    // Field value mutator
    void setValue(const T& value);

    SimpleDataField<T>& operator=(const T& simple_type);

private:

    void copyOptionalSwap(std::uint8_t*   buffer,
                          misc::ByteOrder destination_byte_order) const;

    T simple_data_field;
};

//==============================================================================
template <class T> inline T SimpleDataField<T>::getValue() const
{
    return simple_data_field;
}

//==============================================================================
template <class T> inline void SimpleDataField<T>::getValue(T& value) const
{
    value = simple_data_field;
}

//==============================================================================
template <class T> inline void SimpleDataField<T>::setValue(const T& value)
{
    simple_data_field = value;
}

#endif
