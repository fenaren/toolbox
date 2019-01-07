#if !defined DATA_PACKET_HPP
#define DATA_PACKET_HPP

#include <stdexcept>
#include <vector>

#include "DataField.hpp"

#include "misc.hpp"

class DataPacket : public DataField
{
public:

    // Initializes byte alignment
    explicit DataPacket(unsigned int byte_alignment = 1);

    // Does nothing
    virtual ~DataPacket();

    // Reads the data field from the "buffer" memory location without
    // considering byte ordering.
    virtual unsigned int readRaw(const unsigned char* buffer);

    // Reads this data packet from the "buffer" memory location.  Each field
    // will be byteswapped if its source byte order does not match the byte
    // ordering of the host.
    virtual unsigned int readRaw(const unsigned char* buffer,
                                 misc::ByteOrder      source_byte_order);

    // Writes the data field to the "buffer" memory location without considering
    // byte ordering.
    virtual unsigned int writeRaw(unsigned char* buffer) const;

    // Writes this data packet to the "buffer" memory location.  Each field will
    // be byteswapped if its source byte order does not match the byte ordering
    // of the host.
    virtual unsigned int writeRaw(unsigned char*  buffer,
                                  misc::ByteOrder destination_byte_order) const;

    // Returns the size of this field in bytes.  This will equal the number of
    // bytes written by writeRaw() and read by readRaw().
    virtual unsigned int getLengthBytes() const;

    // Byte alignment access
    unsigned int getByteAlignment() const;

    // Byte alignment mutator
    void setByteAlignment(unsigned int byte_alignment);

protected:

    // Adds the field to the end of the packet.  The field is not maintained
    // internally, only its order relative to other fields in this packet is.
    void addDataField(DataField* data_field);

private:

    // Derived classes should use this to add all their data fields
    virtual void addDataFields() = 0;

    // Computes amount of padding needed after a field given the current byte
    // alignment setting
    unsigned int computePadding(unsigned int field_length) const;

    // All contained data fields ordered first to last
    std::vector<DataField*> data_fields;

    unsigned int byte_alignment;

    // A meaningful deep copy can't be done here so disallow that and operator=
    DataPacket(const DataPacket&);
    DataPacket& operator=(const DataPacket&);
};

inline unsigned int DataPacket::getByteAlignment() const
{
    return byte_alignment;
}

inline void DataPacket::setByteAlignment(unsigned int byte_alignment)
{
    if (byte_alignment == 0)
    {
        throw std::invalid_argument(
            "Nonsensical byte alignment value of 0 specified (must be 1 or "
            "greater)");
    }

    this->byte_alignment = byte_alignment;
}

inline void DataPacket::addDataField(DataField* data_field)
{
    data_fields.push_back(data_field);
}

#endif
