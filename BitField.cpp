#include <cstring>
#include <new>

#include "BitField.hpp"

#include "DataField.hpp"
#include "misc.hpp"

//==============================================================================
// Dynamically allocates and maintains a bit field that is "length_bytes" in
// size internally.  All bits are initially unset (set to 0).
//==============================================================================
BitField::BitField(unsigned int length_bytes) :
    DataField(),
    bit_field_raw_owned(true),
    length_bytes(length_bytes)
{
    bit_field_raw = new std::uint8_t[length_bytes];
    memset(bit_field_raw, 0, length_bytes);
}

//==============================================================================
// Behavior depends on the value of "bit_field_raw_owned".  If
// "bit_field_raw_owned" is true, the data at "buffer" of length "length_bytes"
// will be copied into dynamically-allocated memory internal to this class.  If
// "bit_field_raw_owned" is false, the data at "buffer" of length "length_bytes"
// will be used by this class in-place and no dynamic memory allocation will
// occur.
//==============================================================================
BitField::BitField(std::uint8_t* buffer,
                   unsigned int  length_bytes,
                   bool          bit_field_raw_owned) :
    DataField(),
    bit_field_raw_owned(bit_field_raw_owned),
    length_bytes(length_bytes)
{
    if (bit_field_raw_owned)
    {
        bit_field_raw = new std::uint8_t[length_bytes];
        readRaw(buffer);
    }
    else
    {
        bit_field_raw = buffer;
    }
}

//==============================================================================
// Copy constructor; dynamically allocates and maintains a bit field that is
// "length_bytes" in size, and then copies the given bit field into this
// newly-allocated memory.
//==============================================================================
BitField::BitField(const BitField& bit_field) :
    DataField(),
    bit_field_raw_owned(true)
{
    length_bytes = bit_field.getLengthBytes();

    bit_field_raw = new std::uint8_t[length_bytes];

    bit_field.writeRaw(bit_field_raw);
}

//==============================================================================
// Frees the memory at "bit_field_raw" if owned by this class
//==============================================================================
BitField::~BitField()
{
    if (bit_field_raw_owned)
    {
        delete[] bit_field_raw;
    }
}

//==============================================================================
// Reads a raw bit field from the "buffer" memory location.  Byte ordering has
// no relevance to bit fields so no byte swapping is performed.
//==============================================================================
unsigned int BitField::readRaw(const std::uint8_t* buffer)
{
    return DataField::readRaw(buffer);
}

//==============================================================================
// Reads a raw bit field from the "buffer" memory location.  This function is
// required by the framework to be implemented here, despite being functionally
// identical to the single-argument version defined above.  If byte ordering
// were relevant to bit fields (in the general sense of the term) this function
// would be where that difference would be handled.
//==============================================================================
unsigned int BitField::readRaw(const std::uint8_t* buffer,
                               misc::ByteOrder     source_byte_order)
{
    // No byteswapping regardless of "source_byte_order" setting
    memcpy(bit_field_raw, buffer, length_bytes);
    return length_bytes;
}

//==============================================================================
// Writes this bit field to the "buffer" memory location.  Byte ordering has no
// relevance to bit fields so no byte swapping is performed.
//==============================================================================
unsigned int BitField::writeRaw(std::uint8_t* buffer) const
{
    return DataField::writeRaw(buffer);
}

//==============================================================================
// Writes this bit field to the "buffer" memory location.  This function is
// required by the framework to be implemented here, despite being functionally
// identical to the single-argument version defined above.  If byte ordering
// were relevant to bit fields (in the general sense of the term) this function
// would be where that difference would be handled.
//==============================================================================
unsigned int
BitField::writeRaw(std::uint8_t*   buffer,
                   misc::ByteOrder destination_byte_order) const
{
    // No byteswapping regardless of "destination_byte_order" setting
    memcpy(buffer, bit_field_raw, length_bytes);
    return length_bytes;
}

//==============================================================================
// Assigns a BitField to this BitField
//==============================================================================
BitField& BitField::operator=(const BitField& bit_field)
{
    bit_field.writeRaw(bit_field_raw);
    return *this;
}

//==============================================================================
// Equality comparison, BitField == BitField
//==============================================================================
bool operator==(const BitField& bit_field1, const BitField& bit_field2)
{
    if (bit_field1.getLengthBytes() != bit_field2.getLengthBytes())
    {
        return false;
    }

    // We know both bit fields have equal length at this point
    unsigned int length_bytes = bit_field1.getLengthBytes();

    for (unsigned int i = 0; i < length_bytes; i++)
    {
        if (bit_field1.getOctet(i) != bit_field2.getOctet(i))
        {
            return false;
        }
    }

    return true;
}

//==============================================================================
// Inequality comparison, BitField != BitField
//==============================================================================
bool operator!=(const BitField& bit_field1, const BitField& bit_field2)
{
    return !(bit_field1 == bit_field2);
}
