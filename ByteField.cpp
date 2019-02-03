#include <cstring>
#include <new>
#include <stdexcept>

#include "ByteField.hpp"

#include "DataField.hpp"
#include "misc.hpp"

//==============================================================================
ByteField::ByteField(unsigned long length_bytes) :
    DataField(),
    length_bytes(length_bytes),
    memory_internal(true),
    indexing_mode(misc::MS_ZERO)
{
    byte_field_raw = new std::uint8_t[length_bytes];
    memset(byte_field_raw, 0, length_bytes);
}

//==============================================================================
ByteField::ByteField(std::uint8_t* buffer,
                     unsigned long length_bytes,
                     bool          memory_internal) :
    DataField(),
    length_bytes(length_bytes),
    memory_internal(memory_internal),
    indexing_mode(misc::MS_ZERO)
{
    if (memory_internal)
    {
        byte_field_raw = new std::uint8_t[length_bytes];
        readRaw(buffer);
    }
    else
    {
        byte_field_raw = buffer;
    }
}

//==============================================================================
ByteField::ByteField(const ByteField& byte_field) :
    DataField(),
    memory_internal(true)
{
    length_bytes = byte_field.getLengthBytes();
    indexing_mode = byte_field.getIndexingMode();

    byte_field_raw = new std::uint8_t[length_bytes];

    byte_field.writeRaw(byte_field_raw);
}

//==============================================================================
ByteField::~ByteField()
{
    if (memory_internal)
    {
        delete[] byte_field_raw;
    }
}

//==============================================================================
unsigned long ByteField::readRaw(std::uint8_t* buffer,
                                 unsigned long offset_bits)
{
    return DataField::readRaw(buffer, offset_bits);
}

//==============================================================================
unsigned long ByteField::readRaw(std::uint8_t*   buffer,
                                 misc::ByteOrder source_byte_order,
                                 unsigned long   offset_bits)
{
    // No byteswapping regardless of "source_byte_order" setting
    memcpy(byte_field_raw, buffer, length_bytes);
    return length_bytes;
}

//==============================================================================
unsigned long ByteField::writeRaw(std::uint8_t* buffer,
                                  unsigned long offset_bits) const
{
    return DataField::writeRaw(buffer, offset_bits);
}

//==============================================================================
unsigned long ByteField::writeRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder destination_byte_order,
                                  unsigned long   offset_bits) const
{
    // No byteswapping regardless of "destination_byte_order" setting
    memcpy(buffer, byte_field_raw, length_bytes);
    return length_bytes;
}

//==============================================================================
ByteField& ByteField::operator=(const ByteField& byte_field)
{
    if (this != &byte_field)
    {
        byte_field.writeRaw(byte_field_raw);
    }

    return *this;
}

//==============================================================================
bool operator==(const ByteField& byte_field1, const ByteField& byte_field2)
{
    if (byte_field1.getLengthBytes() != byte_field2.getLengthBytes())
    {
        return false;
    }

    // We know both bit fields have equal length at this point
    unsigned long length_bytes = byte_field1.getLengthBytes();

    for (unsigned long i = 0; i < length_bytes; i++)
    {
        if (byte_field1.getByte(i) != byte_field2.getByte(i))
        {
            return false;
        }
    }

    return true;
}

//==============================================================================
bool operator!=(const ByteField& byte_field1, const ByteField& byte_field2)
{
    return !(byte_field1 == byte_field2);
}
