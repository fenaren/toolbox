#if !defined BIT_FIELD_HPP
#define BIT_FIELD_HPP

#include <bitset>
#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <string>

#include "DataField.hpp"

#include "misc.hpp"

class BitField : public DataField
{
public:

    // Dynamically allocates and maintains a bit field that is "length_bytes" in
    // size.  All bits are initially unset (set to 0).  Storage is dynamically
    // allocated.
    // cppcheck-suppress noExplicitConstructor
    BitField(unsigned int length_bytes);

    // Behavior depends on the value of "memory_internal".  If "memory_internal"
    // is true, the data at "buffer" of length "length_bytes" will be copied
    // into dynamically-allocated memory internal to this class.  If
    // "memory_internal" is false, the data at "buffer" of length "length_bytes"
    // will be used by this class in-place and no dynamic memory allocation will
    // occur.
    BitField(std::uint8_t* buffer,
             unsigned int  length_bytes,
             bool          memory_internal = true);

    // Copy constructor; dynamically allocates and maintains a bit field that is
    // "length_bytes" in size, and then copies the given bit field into this
    // newly-allocated memory.
    BitField(const BitField& bit_field);

    // Will free the memory at "raw_bit_field" if it is owned by this class
    virtual ~BitField();

    // Reads a raw bit field from the "buffer" memory location.  Byte ordering
    // has no relevance to bit fields so no byte swapping is performed.
    virtual unsigned int readRaw(const std::uint8_t* buffer);

    // Reads a raw bit field from the "buffer" memory location.  This
    // function is required by the framework to be implemented here, despite
    // being functionally identical to the single-argument version defined
    // above.  If byte ordering were relevant to bit fields (in the
    // general sense of the term) this function would be where that difference
    // would be handled.
    virtual unsigned int readRaw(const std::uint8_t* buffer,
                                 misc::ByteOrder     source_byte_order);

    // Writes this bit field to the "buffer" memory location.  Byte ordering has
    // no relevance to bit fields so no byte swapping is performed.
    virtual unsigned int writeRaw(std::uint8_t* buffer) const;

    // Writes this bit field to the "buffer" memory location.  This function is
    // required by the framework to be implemented here, despite being
    // functionally identical to the single-argument version defined above.  If
    // byte ordering were relevant to bit fields (in the general sense of the
    // term) this function would be where that difference would be handled.
    virtual unsigned int writeRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder destination_byte_order) const;

    // Octet access
    std::uint8_t getOctet(unsigned int octet) const;

    // Octet mutation; octets are indexed starting from 0 for the byte at the
    // lowest memory address and increasing to the highest memory address
    void setOctet(unsigned int octet, std::uint8_t value);

    // Bit access; bits are indexed starting with 0 for the least significant
    // bit and increasing to the most significant bit
    bool getBit(unsigned int octet, unsigned int octet_bit);
    bool getBit(unsigned int bit);

    // Bit mutation; bits are indexed starting with 0 for the least significant
    // bit and increasing to the most significant bit
    void setBit(unsigned int octet, unsigned int octet_bit, bool value);
    void setBit(unsigned int bit, bool value);

    // Returns the size of this bit field in bytes.  This will equal the number
    // of bytes written by writeRaw() and read by readRaw().
    virtual unsigned int getLengthBytes() const;

    // Simple accessor for memory_internal
    bool getMemoryInternal() const;

    // There are 8 bits in a byte
    static const unsigned int BITS_PER_BYTE = 8;

    BitField& operator=(const BitField& bit_field);

private:

    // Tosses a std::out_of_range exception if octet >= length_bytes
    void throwIfOctetOutOfRange(unsigned int octet) const;

    // Raw bit field is stored at this location
    std::uint8_t* bit_field_raw;

    // Does this class own the memory at "bit_field_raw"?
    bool memory_internal;

    // Raw bit field is this many bytes in length
    unsigned int length_bytes;
};

inline std::uint8_t BitField::getOctet(unsigned int octet) const
{
    throwIfOctetOutOfRange(octet);
    return bit_field_raw[octet];
}

inline void BitField::setOctet(unsigned int octet, std::uint8_t value)
{
    throwIfOctetOutOfRange(octet);
    bit_field_raw[octet] = value;
}

inline bool BitField::getBit(unsigned int octet, unsigned int octet_bit)
{
    throwIfOctetOutOfRange(octet);

    // Use std::bitset to do the bitshifting nonsense for us
    std::bitset<BITS_PER_BYTE> working_octet(bit_field_raw[octet]);
    return working_octet.test(octet_bit);
}

inline bool BitField::getBit(unsigned int bit)
{
    return getBit(std::floor(bit / BITS_PER_BYTE), bit % BITS_PER_BYTE);
}

inline
void BitField::setBit(unsigned int octet, unsigned int octet_bit, bool value)
{
    throwIfOctetOutOfRange(octet);

    // Use std::bitset to do the bitshifting nonsense for us
    std::bitset<BITS_PER_BYTE> working_octet(bit_field_raw[octet]);
    working_octet.set(octet_bit, value);
    bit_field_raw[octet] = static_cast<std::uint8_t>(working_octet.to_ulong());
}

inline void BitField::setBit(unsigned int bit, bool value)
{
    setBit(std::floor(bit / BITS_PER_BYTE), bit % BITS_PER_BYTE, value);
}

inline unsigned int BitField::getLengthBytes() const
{
    return length_bytes;
}

inline bool BitField::getMemoryInternal() const
{
    return memory_internal;
}

inline void BitField::throwIfOctetOutOfRange(unsigned int octet) const
{
    if (octet >= length_bytes)
    {
        throw std::out_of_range("Out-of-range octet index");
    }
}

bool operator==(const BitField& bit_field1, const BitField& bit_field2);
bool operator!=(const BitField& bit_field1, const BitField& bit_field2);

#endif