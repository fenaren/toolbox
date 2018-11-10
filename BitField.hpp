#if !defined BIT_FIELD_HPP
#define BIT_FIELD_HPP

#include <cstdint>
#include <stdexcept>
#include <string>

#include "DataField.hpp"

#include "misc.hpp"

class BitField : public DataField
{
public:

    // Dynamically allocates and maintains a bit field that is "length_bytes" in
    // size internally.  All bits are initially unset (set to 0).
    // cppcheck-suppress noExplicitConstructor
    BitField(unsigned int length_bytes);

    // Behavior depends on the value of "bit_field_raw_owned".  If
    // "bit_field_raw_owned" is true, the data at "buffer" of length
    // "length_bytes" will be copied into dynamically-allocated memory internal
    // to this class.  If "bit_field_raw_owned" is false, the data at "buffer"
    // of length "length_bytes" will be used by this class in-place and no
    // dynamic memory allocation will occur.
    BitField(unsigned char* buffer,
             unsigned int   length_bytes,
             bool           bit_field_raw_owned = true);

    // Copy constructor; dynamically allocates and maintains a bit field that is
    // "length_bytes" in size, and then copies the given bit field into this
    // newly-allocated memory.
    BitField(const BitField& bit_field);

    // Will free the memory at "raw_bit_field" if it is owned by this class
    virtual ~BitField();

    // Reads a raw bit field from the "buffer" memory location.  Byte ordering
    // has no relevance to bit fields so no byte swapping is performed.
    virtual unsigned int readRaw(const unsigned char* buffer);

    // Reads a raw bit field from the "buffer" memory location.  This
    // function is required by the framework to be implemented here, despite
    // being functionally identical to the single-argument version defined
    // above.  If byte ordering were relevant to bit fields (in the
    // general sense of the term) this function would be where that difference
    // would be handled.
    virtual unsigned int readRaw(const unsigned char* buffer,
                                 misc::ByteOrder      source_byte_order);

    // Writes this bit field to the "buffer" memory location.  Byte ordering has
    // no relevance to bit fields so no byte swapping is performed.
    virtual unsigned int writeRaw(unsigned char* buffer) const;

    // Writes this bit field to the "buffer" memory location.  This function is
    // required by the framework to be implemented here, despite being
    // functionally identical to the single-argument version defined above.  If
    // byte ordering were relevant to bit fields (in the general sense of the
    // term) this function would be where that difference would be handled.
    virtual unsigned int writeRaw(unsigned char*  buffer,
                                  misc::ByteOrder destination_byte_order) const;

    // Octet access
    unsigned char getOctet(unsigned int octet) const;

    // Octet mutation
    void setOctet(unsigned int octet, unsigned char value);

    // Returns the size of this bit field in bytes.  This will equal the number
    // of bytes written by writeRaw() and read by readRaw().
    virtual unsigned int getLengthBytes() const;

    // Simple accessor for bit_field_raw_owned
    bool getBitFieldRawOwned() const;

    BitField& operator=(const BitField& bit_field);

private:

    // Raw bit field is stored at this location
    unsigned char* bit_field_raw;

    // Does this class own the memory at "bit_field_raw"?
    bool bit_field_raw_owned;

    // Raw bit field is this many bytes in length
    unsigned int length_bytes;
};

inline std::uint8_t BitField::getOctet(unsigned int octet) const
{
    if (octet >= length_bytes)
    {
        throw std::out_of_range("Out-of-range octet specified");
    }

    return bit_field_raw[octet];
}

inline void BitField::setOctet(unsigned int octet, unsigned char value)
{
    if (octet >= length_bytes)
    {
        throw std::out_of_range("Out-of-range octet specified");
    }

    bit_field_raw[octet] = value;
}

inline unsigned int BitField::getLengthBytes() const
{
    return length_bytes;
}

inline bool BitField::getBitFieldRawOwned() const
{
    return bit_field_raw_owned;
}

bool operator==(const BitField& bit_field1,
                const BitField& bit_field2);

bool operator!=(const BitField& bit_field1,
                const BitField& bit_field2);

#endif
