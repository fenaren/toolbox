#if !defined DATA_PACKET_HPP
#define DATA_PACKET_HPP

#include <stdexcept>
#include <cstdint>
#include <vector>

#include "DataField.hpp"

#include "misc.hpp"

class DataPacket : public DataField
{
public:

    enum AlignmentUnits
    {
        BITS,
        BYTES
    };

    // Initializes byte alignment
    DataPacket(unsigned int   alignment = 1,
               AlignmentUnits alignment_units = BYTES);

    // Does nothing
    virtual ~DataPacket();

    unsigned long readRaw(std::uint8_t* buffer);

    unsigned long readRaw(std::uint8_t*   buffer,
                          misc::ByteOrder source_byte_order);

    unsigned long readRaw(std::uint8_t* buffer,
                          unsigned long offset_bits);

    // Reads this data packet from the "buffer" memory location.  Each field
    // will be byteswapped if its source byte order does not match the byte
    // ordering of the host.
    virtual unsigned long readRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder source_byte_order,
                                  unsigned long   offset_bits);

    unsigned long writeRaw(std::uint8_t* buffer) const;

    unsigned long writeRaw(std::uint8_t*   buffer,
                           misc::ByteOrder destination_byte_order) const;

    unsigned long writeRaw(std::uint8_t* buffer,
                           unsigned long offset_bits) const;

    // Writes this data packet to the "buffer" memory location.  Each field will
    // be byteswapped if its source byte order does not match the byte ordering
    // of the host.
    virtual unsigned long writeRaw(std::uint8_t*  buffer,
                                  misc::ByteOrder destination_byte_order,
                                  unsigned long   offset_bits) const;

    // Returns the size of this field in bytes.  This will equal the number of
    // bytes written by writeRaw() and read by readRaw().
    virtual unsigned long getLengthBits() const;

    // Alignment access
    unsigned int getAlignment(AlignmentUnits alignment_units = BYTES) const;

    // Alignment mutator
    void setAlignment(unsigned int   alignment,
                      AlignmentUnits alignment_units = BYTES);

protected:

    // Adds the field to the end of the packet.  The field is not maintained
    // internally, only its order relative to other fields in this packet is.
    void addDataField(DataField* data_field);

private:

    // Derived classes should use this to add all their data fields
    virtual void addDataFields() = 0;

    // All contained data fields ordered first to last
    std::vector<DataField*> data_fields;

    unsigned int alignment_bits;

    // A meaningful deep copy can't be done here so disallow that and operator=
    DataPacket(const DataPacket&);
    DataPacket& operator=(const DataPacket&);
};

inline
unsigned int DataPacket::getAlignment(AlignmentUnits alignment_units) const
{
    if (alignment_units == BYTES)
    {
        if (alignment_bits % BITS_PER_BYTE != 0)
        {
            throw std::runtime_error(
                "Alignment cannot be represented in bytes as an integer");
        }

        return alignment_bits / BITS_PER_BYTE;
    }

    return alignment_bits;
}

inline void DataPacket::setAlignment(unsigned int   alignment,
                                     AlignmentUnits alignment_units)
{
    if (alignment == 0)
    {
        throw std::invalid_argument("Alignment must be greater than 0");
    }

    if (alignment_units == BYTES)
    {
        alignment *= BITS_PER_BYTE;
    }

    alignment_bits = alignment;
}

inline void DataPacket::addDataField(DataField* data_field)
{
    data_fields.push_back(data_field);
}

#endif
